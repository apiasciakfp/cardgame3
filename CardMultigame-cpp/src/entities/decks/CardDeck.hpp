#pragma once

#include "entities/cards/Card.hpp"
#include "technical/rangens/ICardSelector.hpp"

#include <memory>
#include <string>
#include <vector>

namespace cardmultigame::entities::decks
{
    class CardDeck
    {
        std::shared_ptr<technical::rangens::ICardSelector> _selector;
        std::vector<std::shared_ptr<cards::Card>> _cards;

    public:
        CardDeck(std::shared_ptr<technical::rangens::ICardSelector> selector, std::vector<std::shared_ptr<cards::Card>> cards);

        // Returns the internal list BY REFERENCE (WART-3), not a copy.
        std::vector<std::shared_ptr<cards::Card>>& AllCards();
        int CardsLeft() const;

        std::shared_ptr<cards::Card> DrawRandomCard();
        std::shared_ptr<cards::Card> DrawLastAddedCard();
        void AddASingleCard(std::shared_ptr<cards::Card> card);

        std::string ToString() const;
    };
}
