#include "entities/decks/CreateCardDeck.hpp"

#include "entities/cards/CreateCards.hpp"
#include "technical/rangens/RandomCardSelector.hpp"

#include <vector>

namespace cardmultigame::entities::decks
{
    CreateCardDeck::CreateCardDeck()
        : _selectedCardSelector(std::make_shared<technical::rangens::RandomCardSelector>())
    {
    }

    std::shared_ptr<CardDeck> CreateCardDeck::FromGivenCards(const std::string& cardsInDeck)
    {
        std::vector<std::shared_ptr<cards::Card>> cards = cards::CreateCards().CreateCollection(cardsInDeck);
        return std::make_shared<CardDeck>(_selectedCardSelector, cards);
    }

    std::shared_ptr<CardDeck> CreateCardDeck::Simple9ToAWith4Colours()
    {
        const std::vector<std::string> ranks = {"9", "10", "J", "Q", "K", "A"};
        const std::vector<std::string> colours = {"S", "H", "D", "C"};

        std::vector<std::shared_ptr<cards::Card>> cards;
        for (const auto& rank : ranks)
        {
            for (const auto& colour : colours)
            {
                const std::string cardPrototype = rank + colour;
                cards.push_back(cards::CreateCards().CreateSingle(cardPrototype));
            }
        }

        return std::make_shared<CardDeck>(_selectedCardSelector, cards);
    }

    std::shared_ptr<CardDeck> CreateCardDeck::Simple2ToAWith4Colours()
    {
        const std::vector<std::string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
        const std::vector<std::string> colours = {"S", "H", "D", "C"};

        std::vector<std::shared_ptr<cards::Card>> cards;
        for (const auto& rank : ranks)
        {
            for (const auto& colour : colours)
            {
                const std::string cardPrototype = rank + colour;
                cards.push_back(cards::CreateCards().CreateSingle(cardPrototype));
            }
        }

        return std::make_shared<CardDeck>(_selectedCardSelector, cards);
    }

    std::shared_ptr<CardDeck> CreateCardDeck::Empty()
    {
        return std::make_shared<CardDeck>(_selectedCardSelector, std::vector<std::shared_ptr<cards::Card>>{});
    }

    void CreateCardDeck::SetCardSelector(std::shared_ptr<technical::rangens::ICardSelector> selector)
    {
        _selectedCardSelector = std::move(selector);
    }
}
