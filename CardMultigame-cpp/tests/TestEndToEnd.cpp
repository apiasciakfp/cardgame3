#include "doctest.h"

#include "entities/decks/CardDeck.hpp"
#include "entities/decks/CreateCardDeck.hpp"
#include "entities/gamestates/CreateGameState.hpp"
#include "entities/gamestates/GameState.hpp"
#include "entities/gamestates/GameStateKeys.hpp"
#include "gamemanagers/GameManager.hpp"
#include "gamemanagers/selectedrules/CreatePlayedGameRules.hpp"
#include "gamemanagers/selectedrules/PlayedGameRules.hpp"
#include "technical/rangens/AlwaysFirstSelector.hpp"
#include "usecases/cardcomparison/StrictCardComparisonStrategy.hpp"
#include "usecases/gameactions/GuessCardAction.hpp"
#include "usecases/gameactions/IGameAction.hpp"
#include "usecases/gameconditions/DidGuessACard.hpp"
#include "usecases/gameconditions/DidTurnsExpire.hpp"
#include "usecases/gameconditions/IGameCondition.hpp"
#include "usecases/influencestate/QueryGameState.hpp"

#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>

using namespace cardmultigame;
using entities::gamestates::GameState;
using entities::gamestates::GameStateKeys;
using gamemanagers::GameManager;
using Query = usecases::influencestate::QueryGameState;

TEST_CASE("fullScenario_setup_miss_hit_victory_thenGameIgnoresCommands")
{
    // SETUP: "Play GuessACard; SetDeck JH,QH,KH; SetMaxTurns 3; SETUP" — deterministic via AlwaysFirst.
    entities::decks::CreateCardDeck deckFactory;
    deckFactory.SetCardSelector(std::make_shared<technical::rangens::AlwaysFirstSelector>());
    std::shared_ptr<entities::decks::CardDeck> deck = deckFactory.FromGivenCards("JH,QH,KH");

    GameState initialState = entities::gamestates::CreateGameState().DefaultsPlusDeck(deck);
    initialState.Set(GameStateKeys::MaxTurns, 3);

    std::vector<std::shared_ptr<usecases::gameactions::IGameAction>> actions = {
        std::make_shared<usecases::gameactions::GuessCardAction>()};
    std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>> victories = {
        std::make_shared<usecases::gameconditions::DidGuessACard>()};
    std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>> gameStops = {
        std::make_shared<usecases::gameconditions::DidTurnsExpire>()};

    auto rules = gamemanagers::selectedrules::CreatePlayedGameRules().WithModifications(
        std::optional<std::string>("Guess a Card!"),
        actions, victories, gameStops,
        std::make_shared<usecases::cardcomparison::StrictCardComparisonStrategy>());

    GameManager gm(initialState, rules);

    // ---- initial state after setup ----
    {
        GameState& state = gm.CurrentState();
        CHECK(Query::AmountOfCardsLeft(state) == 3);
        CHECK(Query::MaximumTurns(state) == 3);
        CHECK(Query::CurrentTurn(state) == 0);
        CHECK(Query::IsGameFinished(state) == false);
        CHECK(Query::GameUndergoing(state) == "Undergoing");
    }

    // ---- TURN 1: "Guess 2C;" -> draws JH, miss ----
    gm.ExecuteOrders("Guess 2C;");
    {
        GameState& state = gm.CurrentState();
        CHECK(std::any_cast<bool>(state.Get("Guess")) == false);
        CHECK(Query::CurrentTurn(state) == 1);
        CHECK(Query::AmountOfCardsLeft(state) == 2);
        CHECK(Query::IsGameFinished(state) == false);
        CHECK(Query::GameUndergoing(state) == "Undergoing");
    }

    // ---- TURN 2: "Guess QH;" -> draws QH, hit -> Victory ----
    gm.ExecuteOrders("Guess QH;");
    {
        GameState& state = gm.CurrentState();
        CHECK(std::any_cast<bool>(state.Get("Guess")) == true);
        CHECK(Query::CurrentTurn(state) == 2);
        CHECK(Query::AmountOfCardsLeft(state) == 1);
        CHECK(Query::IsGameFinished(state) == true);
        CHECK(Query::GameUndergoing(state) == "Victory");
    }

    // ---- TURN 3: "Guess KH;" -> ignored (game finished) ----
    gm.ExecuteOrders("Guess KH;");
    {
        GameState& state = gm.CurrentState();
        CHECK(Query::CurrentTurn(state) == 2);
        CHECK(Query::AmountOfCardsLeft(state) == 1);
        CHECK(Query::GameUndergoing(state) == "Victory");
    }
}
