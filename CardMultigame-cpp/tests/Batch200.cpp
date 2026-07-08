#include "doctest.h"

#include "entities/cards/Card.hpp"
#include "entities/decks/CardDeck.hpp"
#include "entities/decks/CreateCardDeck.hpp"
#include "entities/games/guessing/GuessACardGame.hpp"
#include "entities/gamestates/CreateGameState.hpp"
#include "entities/gamestates/GameState.hpp"
#include "entities/gamestates/GameStateKeys.hpp"
#include "gamemanagers/GameManagerInternalsBuilder.hpp"
#include "gamemanagers/selectedrules/CreatePlayedGameRules.hpp"
#include "gamemanagers/selectedrules/PlayedGameRules.hpp"
#include "gamemanagers/selectedrules/creationcommands/GameVariant.hpp"
#include "gamemanagers/selectedrules/creationcommands/ICreateGameRulesCommand.hpp"
#include "gamemanagers/selectedrules/creationcommands/SelectGame.hpp"
#include "gamemanagers/selectedrules/creationcommands/SetDeck.hpp"
#include "usecases/cardcomparison/AlwaysFailComparisonStrategy.hpp"
#include "usecases/cardcomparison/BlackRedColourOnlyComparisonStrategy.hpp"
#include "usecases/cardcomparison/StrictCardComparisonStrategy.hpp"
#include "usecases/gameactions/Add10COrDrawACard.hpp"
#include "usecases/gameactions/AddQueenOfHeartsToDeck.hpp"
#include "usecases/gameactions/CreateGameActions.hpp"
#include "usecases/gameactions/DrawSingleCardAction.hpp"
#include "usecases/gameactions/GuessCardAction.hpp"
#include "usecases/gameactions/IGameAction.hpp"
#include "usecases/gameconditions/DidGuessACard.hpp"
#include "usecases/gameconditions/DidTurnsExpire.hpp"
#include "usecases/gameconditions/IGameCondition.hpp"
#include "usecases/influencestate/ModifyGameState.hpp"
#include "usecases/influencestate/QueryGameState.hpp"

#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

using namespace cardmultigame;
using entities::games::guessing::GuessACardGame;
using entities::gamestates::GameState;
using gamemanagers::GameManagerInternalsBuilder;
using gamemanagers::selectedrules::CreatePlayedGameRules;
using gamemanagers::selectedrules::PlayedGameRules;
namespace cc = usecases::cardcomparison;
namespace ga = usecases::gameactions;
namespace gc = usecases::gameconditions;
namespace cmd = gamemanagers::selectedrules::creationcommands;
using Query = usecases::influencestate::QueryGameState;

template <typename T, typename U>
static bool isInstance(const std::shared_ptr<U>& ptr)
{
    return std::dynamic_pointer_cast<T>(ptr) != nullptr;
}

TEST_CASE("t108_letsPrepareTheStrategyForTheFuture")
{
    auto selectedStrategy = GuessACardGame().CardComparisonStrategy();
    CHECK(isInstance<cc::StrictCardComparisonStrategy>(selectedStrategy));
}

TEST_CASE("t209_theGameWasAStrategyAllAlong")
{
    GuessACardGame game;

    CHECK(game.AvailableActions().size() == 1);
    CHECK(game.GameStopConditions().size() == 1);
    CHECK(game.VictoryConditions().size() == 1);

    CHECK(isInstance<ga::GuessCardAction>(game.AvailableActions()[0]));
    CHECK(isInstance<gc::DidTurnsExpire>(game.GameStopConditions()[0]));
    CHECK(isInstance<gc::DidGuessACard>(game.VictoryConditions()[0]));
}

TEST_CASE("t210_builderPatternRevealsItself")
{
    GameManagerInternalsBuilder builder;
    cmd::SelectGame().ChangeGameRuleset(builder, "GuessACard");

    auto rules = builder.ConstructRuleset();

    CHECK(isInstance<cc::StrictCardComparisonStrategy>(rules->CardComparator()));
    CHECK(isInstance<ga::GuessCardAction>(rules->GameActions()[0]));
    CHECK(isInstance<gc::DidTurnsExpire>(rules->GameStopConditions()[0]));
    CHECK(isInstance<gc::DidGuessACard>(rules->VictoryConditions()[0]));
}

TEST_CASE("t211_gloryOfDeferredConstruction")
{
    GameManagerInternalsBuilder builder;

    std::vector<std::shared_ptr<cmd::ICreateGameRulesCommand>> commands = {
        std::make_shared<cmd::SelectGame>(), std::make_shared<cmd::GameVariant>()};
    std::vector<std::string> arguments = {"GuessACard", "RedBlack"};

    for (std::size_t i = 0; i < commands.size(); ++i)
    {
        commands[i]->ChangeGameRuleset(builder, arguments[i]);
    }

    auto rules = builder.ConstructRuleset();

    CHECK(isInstance<cc::BlackRedColourOnlyComparisonStrategy>(rules->CardComparator()));
    CHECK(isInstance<ga::GuessCardAction>(rules->GameActions()[0]));
    CHECK(isInstance<gc::DidTurnsExpire>(rules->GameStopConditions()[0]));
    CHECK(isInstance<gc::DidGuessACard>(rules->VictoryConditions()[0]));
}

TEST_CASE("t212_implementGuessACardCommand")
{
    GameManagerInternalsBuilder builder;

    std::vector<std::shared_ptr<cmd::ICreateGameRulesCommand>> commands = {
        std::make_shared<cmd::SelectGame>(), std::make_shared<cmd::GameVariant>(), std::make_shared<cmd::SetDeck>()};
    std::vector<std::string> arguments = {"GuessACard", "RedBlack", "2H,2D,3H,3D"};

    for (std::size_t i = 0; i < commands.size(); ++i)
    {
        commands[i]->ChangeGameRuleset(builder, arguments[i]);
    }

    auto rules = builder.ConstructRuleset();
    GameState gameState = builder.ConstructGameState();

    CHECK(Query::AmountOfCardsLeft(gameState) == 4);

    ga::GuessCardAction action;

    // First guess 2S (black) vs a red card -> miss.
    action.ChangeGameState(gameState, *rules, "2S");
    CHECK(std::any_cast<bool>(gameState.Get("Guess")) == false);

    // Second guess 10H (red) vs a red card -> hit.
    action.ChangeGameState(gameState, *rules, "10H");
    CHECK(std::any_cast<bool>(gameState.Get("Guess")) == true);
}

TEST_CASE("t213_oneMoreFactory_withNullObject")
{
    auto referenceRules = CreatePlayedGameRules().Empty();

    CHECK(referenceRules->GameActions().size() == 0);
    CHECK(referenceRules->VictoryConditions().size() == 0);
    CHECK(referenceRules->GameStopConditions().size() == 0);
    CHECK(isInstance<cc::AlwaysFailComparisonStrategy>(referenceRules->CardComparator()));

    const std::string gameName = "Random game";

    auto actualRules = CreatePlayedGameRules().WithModifications(
        std::optional<std::string>(gameName), std::nullopt, std::nullopt, std::nullopt, nullptr);

    CHECK(actualRules->GameName() == gameName);
    CHECK(actualRules->GameActions().size() == referenceRules->GameActions().size());
    CHECK(actualRules->VictoryConditions().size() == referenceRules->VictoryConditions().size());
    CHECK(actualRules->GameStopConditions().size() == referenceRules->GameStopConditions().size());
    CHECK(isInstance<cc::AlwaysFailComparisonStrategy>(actualRules->CardComparator()));

    std::vector<std::shared_ptr<ga::IGameAction>> actions = {std::make_shared<ga::GuessCardAction>()};
    std::vector<std::shared_ptr<gc::IGameCondition>> victories = {std::make_shared<gc::DidGuessACard>()};

    actualRules = CreatePlayedGameRules().WithModifications(
        std::nullopt, std::optional(actions), std::optional(victories), std::nullopt, nullptr);

    CHECK(actualRules->GameName() == referenceRules->GameName());
    CHECK(isInstance<ga::GuessCardAction>(actualRules->GameActions()[0]));
    CHECK(isInstance<gc::DidGuessACard>(actualRules->VictoryConditions()[0]));
    CHECK(actualRules->GameStopConditions().size() == referenceRules->GameStopConditions().size());
    CHECK(isInstance<cc::AlwaysFailComparisonStrategy>(actualRules->CardComparator()));
}

// ---- Slice 5: dormant special-rule actions ----
// The C# tests pass `null` for rules/params; C++ has no null references, so the dormant actions (which
// ignore both) receive a dummy empty PlayedGameRules and "" — behavior-identical, orthography only.

namespace
{
    using entities::decks::CardDeck;
    using entities::decks::CreateCardDeck;
    using entities::gamestates::CreateGameState;
    using entities::gamestates::GameState;
    using entities::gamestates::GameStateKeys;
    using Modify = usecases::influencestate::ModifyGameState;
}

TEST_CASE("t201_gentleIntroductionToCommand")
{
    auto dummyRules = CreatePlayedGameRules().Empty();

    GameState tutorialState = CreateGameState().DefaultsWithFullDeck();
    Query::ExtractCardDeck(tutorialState)->DrawRandomCard();

    std::shared_ptr<CardDeck> deck = CreateCardDeck().FromGivenCards("2H, 3H, 4H");
    GameState gameState = CreateGameState().DefaultsPlusDeck(deck);

    CHECK(Query::AmountOfCardsLeft(gameState) == 3);
    const int amountOfCardsAfterDrawingOne = Query::AmountOfCardsLeft(gameState) - 1;

    ga::DrawSingleCardAction().ChangeGameState(gameState, *dummyRules, "");

    CHECK(Query::AmountOfCardsLeft(gameState) == amountOfCardsAfterDrawingOne);
}

TEST_CASE("t202_addSome_QH_intoTheCardDeck")
{
    auto dummyRules = CreatePlayedGameRules().Empty();

    std::shared_ptr<CardDeck> deck = CreateCardDeck().FromGivenCards("2H, 3H, 4H");
    GameState gameState = CreateGameState().DefaultsPlusDeck(deck);

    std::vector<std::shared_ptr<ga::IGameAction>> actions = {
        std::make_shared<ga::AddQueenOfHeartsToDeck>(), std::make_shared<ga::AddQueenOfHeartsToDeck>(),
        std::make_shared<ga::AddQueenOfHeartsToDeck>(), std::make_shared<ga::AddQueenOfHeartsToDeck>(),
        std::make_shared<ga::AddQueenOfHeartsToDeck>()};

    CHECK(Query::AmountOfCardsLeft(gameState) == 3);
    const int amountAfter = Query::AmountOfCardsLeft(gameState) + static_cast<int>(actions.size());

    for (const auto& action : actions) action->ChangeGameState(gameState, *dummyRules, "");

    CHECK(Query::AmountOfCardsLeft(gameState) == amountAfter);

    std::shared_ptr<CardDeck> retrievedDeck = Query::ExtractCardDeck(gameState);
    for (int i = 0; i < 5; ++i)
    {
        auto card = retrievedDeck->DrawLastAddedCard();
        CHECK(card->Rank() == "Q");
        CHECK(card->Colour() == "H");
    }
}

TEST_CASE("t203_chainSomeCommands")
{
    auto dummyRules = CreatePlayedGameRules().Empty();

    std::shared_ptr<CardDeck> deck = CreateCardDeck().FromGivenCards("2H, 3H, 4H");
    GameState gameState = CreateGameState().DefaultsPlusDeck(deck);

    std::vector<std::shared_ptr<ga::IGameAction>> actions = {
        std::make_shared<ga::DrawSingleCardAction>(), std::make_shared<ga::DrawSingleCardAction>(),
        std::make_shared<ga::DrawSingleCardAction>(), std::make_shared<ga::AddQueenOfHeartsToDeck>(),
        std::make_shared<ga::AddQueenOfHeartsToDeck>(), std::make_shared<ga::Add10COrDrawACard>(),
        std::make_shared<ga::Add10COrDrawACard>()};

    CHECK(Query::AmountOfCardsLeft(gameState) == 3);

    for (const auto& action : actions) action->ChangeGameState(gameState, *dummyRules, "");

    CHECK(Query::AmountOfCardsLeft(gameState) == 2);
}

TEST_CASE("t204_factorizeMe")
{
    auto dummyRules = CreatePlayedGameRules().Empty();

    std::shared_ptr<CardDeck> deck = CreateCardDeck().FromGivenCards("2H, 3H, 4H");
    GameState gameState = CreateGameState().DefaultsPlusDeck(deck);

    const std::string actionsToPerform = "drawSingleCard, drawSingleCard, drawSingleCard, addQH, addQH, add10cOrDraw, add10cOrDraw";
    auto actions = ga::CreateGameActions().HavingOrders(actionsToPerform);

    CHECK(Query::AmountOfCardsLeft(gameState) == 3);

    for (const auto& action : actions) action->ChangeGameState(gameState, *dummyRules, "");

    CHECK(Query::AmountOfCardsLeft(gameState) == 2);
}

TEST_CASE("t205_commandsCanCommunicateViaContext")
{
    auto dummyRules = CreatePlayedGameRules().Empty();

    GameState tutorialState = CreateGameState().Default();
    CHECK(tutorialState.Get("SpecificKey").has_value() == false);
    tutorialState.Set("SpecificKey", std::string("Capybara"));
    CHECK(std::any_cast<std::string>(tutorialState.Get("SpecificKey")) == "Capybara");

    std::shared_ptr<CardDeck> deck = CreateCardDeck().FromGivenCards("2H, 3H, 4H");
    GameState gameState = CreateGameState().DefaultsPlusDeck(deck);

    auto actions = ga::CreateGameActions().HavingOrders("drawSingleCard, drawSingleCard, drawSingleCard");

    CHECK(Query::AmountOfCardsLeft(gameState) == 3);

    for (const auto& action : actions) action->ChangeGameState(gameState, *dummyRules, "");

    CHECK(std::any_cast<bool>(gameState.Get("Guess")) == true);
}

TEST_CASE("t206_queryGameState_cannotChangeAThing")
{
    GameState gameState = CreateGameState().Default();
    gameState.Set(GameStateKeys::IsGameWon, false);
    gameState.Set(GameStateKeys::IsGameLost, false);

    CHECK(Query::IsGameWon(gameState) == false);
    CHECK(Query::IsGameLost(gameState) == false);
}

TEST_CASE("t207_modifyGameState_canChangeQuiteALot")
{
    GameState gameState = CreateGameState().Default();
    gameState.Set(GameStateKeys::IsGameWon, false);
    gameState.Set(GameStateKeys::IsGameLost, false);

    CHECK(Query::IsGameWon(gameState) == false);
    CHECK(Query::IsGameLost(gameState) == false);

    Modify::DeclareGameToBeWon(gameState);
    Modify::DeclareGameToBeLost(gameState);

    CHECK(Query::IsGameWon(gameState) == true);
    CHECK(Query::IsGameLost(gameState) == true);
}

TEST_CASE("t208_winConditionLossCondition")
{
    auto dummyRules = CreatePlayedGameRules().Empty();

    GameState gameState = CreateGameState().DefaultsWithFullDeck();

    auto actions = ga::CreateGameActions().HavingOrders("drawSingleCard, drawSingleCard");

    std::vector<std::shared_ptr<gc::IGameCondition>> conditions = {
        std::make_shared<gc::DidGuessACard>(), std::make_shared<gc::DidTurnsExpire>()};

    do
    {
        for (const auto& action : actions) action->ChangeGameState(gameState, *dummyRules, "");
        for (const auto& condition : conditions) condition->CheckAndUpdate(gameState);
    } while (Query::IsGameFinished(gameState) == false);

    CHECK(Query::IsGameLost(gameState) == true);
    CHECK(Query::IsGameWon(gameState) == false);
}
