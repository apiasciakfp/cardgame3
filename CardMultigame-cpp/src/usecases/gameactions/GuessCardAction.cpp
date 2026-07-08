#include "usecases/gameactions/GuessCardAction.hpp"

#include "entities/cards/Card.hpp"
#include "entities/cards/CreateCards.hpp"
#include "entities/decks/CardDeck.hpp"
#include "gamemanagers/selectedrules/PlayedGameRules.hpp"
#include "technical/StringUtils.hpp"
#include "usecases/cardcomparison/ICardComparisonStrategy.hpp"
#include "usecases/influencestate/ModifyGameState.hpp"
#include "usecases/influencestate/QueryGameState.hpp"

#include <memory>

namespace cardmultigame::usecases::gameactions
{
    void GuessCardAction::ChangeGameState(entities::gamestates::GameState& currentGameState,
                                          gamemanagers::selectedrules::PlayedGameRules& rules,
                                          const std::string& orderParams)
    {
        std::shared_ptr<entities::cards::Card> candidate = entities::cards::CreateCards().CreateSingle(orderParams);

        std::shared_ptr<entities::decks::CardDeck> deck = influencestate::QueryGameState::ExtractCardDeck(currentGameState);
        std::shared_ptr<entities::cards::Card> actuallyDrawnCard = deck->DrawRandomCard();

        std::shared_ptr<cardcomparison::ICardComparisonStrategy> comparator = rules.CardComparator();

        const bool areTheSame = comparator->AreTheSame(candidate, actuallyDrawnCard);

        if (areTheSame) currentGameState.Set(_identifier, true);
        else currentGameState.Set(_identifier, false);

        influencestate::ModifyGameState::AddTurn(currentGameState);
    }

    bool GuessCardAction::ShouldReactTo(const std::string& orderName)
    {
        return technical::ToLower(_identifier) == technical::ToLower(orderName);
    }
}
