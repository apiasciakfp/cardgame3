#include "entities/games/guessing/GuessACardGame.hpp"

#include "entities/decks/CreateCardDeck.hpp"
#include "entities/gamestates/GameStateKeys.hpp"
#include "usecases/cardcomparison/StrictCardComparisonStrategy.hpp"
#include "usecases/gameactions/GuessCardAction.hpp"
#include "usecases/gameconditions/DidGuessACard.hpp"
#include "usecases/gameconditions/DidTurnsExpire.hpp"

namespace cardmultigame::entities::games::guessing
{
    std::string GuessACardGame::Title()
    {
        return "Guess a Card!";
    }

    std::shared_ptr<decks::CardDeck> GuessACardGame::CardDeck()
    {
        return decks::CreateCardDeck().Simple9ToAWith4Colours();
    }

    std::vector<std::shared_ptr<usecases::gameactions::IGameAction>> GuessACardGame::AvailableActions()
    {
        return {std::make_shared<usecases::gameactions::GuessCardAction>()};
    }

    std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>> GuessACardGame::VictoryConditions()
    {
        return {std::make_shared<usecases::gameconditions::DidGuessACard>()};
    }

    std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>> GuessACardGame::GameStopConditions()
    {
        return {std::make_shared<usecases::gameconditions::DidTurnsExpire>()};
    }

    gamestates::GameState GuessACardGame::InitialGameState()
    {
        // A bare modifier holding only MaxTurns=5 (NOT a full Default) — overlaid in WithModifications.
        gamestates::GameState state;
        state.Set(gamestates::GameStateKeys::MaxTurns, 5);
        return state;
    }

    std::shared_ptr<usecases::cardcomparison::ICardComparisonStrategy> GuessACardGame::CardComparisonStrategy()
    {
        return std::make_shared<usecases::cardcomparison::StrictCardComparisonStrategy>();
    }
}
