#include "usecases/gameactions/AddQueenOfHeartsToDeck.hpp"

#include "entities/cards/Card.hpp"
#include "entities/decks/CardDeck.hpp"
#include "technical/NotImplementedException.hpp"
#include "usecases/influencestate/QueryGameState.hpp"

#include <memory>

namespace cardmultigame::usecases::gameactions
{
    void AddQueenOfHeartsToDeck::ChangeGameState(entities::gamestates::GameState& currentGameState,
                                                 gamemanagers::selectedrules::PlayedGameRules&,
                                                 const std::string&)
    {
        std::shared_ptr<entities::decks::CardDeck> deck = influencestate::QueryGameState::ExtractCardDeck(currentGameState);
        deck->AddASingleCard(std::make_shared<entities::cards::Card>("Q", "H"));
    }

    bool AddQueenOfHeartsToDeck::ShouldReactTo(const std::string&)
    {
        throw technical::NotImplementedException();
    }
}
