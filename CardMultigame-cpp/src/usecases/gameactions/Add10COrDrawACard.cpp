#include "usecases/gameactions/Add10COrDrawACard.hpp"

#include "entities/cards/Card.hpp"
#include "entities/decks/CardDeck.hpp"
#include "technical/NotImplementedException.hpp"
#include "usecases/influencestate/QueryGameState.hpp"

#include <memory>

namespace cardmultigame::usecases::gameactions
{
    void Add10COrDrawACard::ChangeGameState(entities::gamestates::GameState& currentGameState,
                                            gamemanagers::selectedrules::PlayedGameRules&,
                                            const std::string&)
    {
        std::shared_ptr<entities::decks::CardDeck> deck = influencestate::QueryGameState::ExtractCardDeck(currentGameState);

        if (influencestate::QueryGameState::AmountOfCardsLeft(currentGameState) % 2 == 0)
        {
            deck->AddASingleCard(std::make_shared<entities::cards::Card>("10", "C"));
        }
        else
        {
            deck->DrawRandomCard();
        }
    }

    bool Add10COrDrawACard::ShouldReactTo(const std::string&)
    {
        throw technical::NotImplementedException();
    }
}
