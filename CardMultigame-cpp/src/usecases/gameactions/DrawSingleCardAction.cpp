#include "usecases/gameactions/DrawSingleCardAction.hpp"

#include "entities/decks/CardDeck.hpp"
#include "technical/NotImplementedException.hpp"
#include "usecases/influencestate/QueryGameState.hpp"

namespace cardmultigame::usecases::gameactions
{
    void DrawSingleCardAction::ChangeGameState(entities::gamestates::GameState& currentGameState,
                                               gamemanagers::selectedrules::PlayedGameRules&,
                                               const std::string&)
    {
        influencestate::QueryGameState::ExtractCardDeck(currentGameState)->DrawRandomCard();

        if (influencestate::QueryGameState::AmountOfCardsLeft(currentGameState) == 0)
        {
            currentGameState.Set("Guess", true);
        }
    }

    bool DrawSingleCardAction::ShouldReactTo(const std::string&)
    {
        throw technical::NotImplementedException();
    }
}
