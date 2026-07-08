#pragma once

#include "entities/decks/CardDeck.hpp"
#include "technical/rangens/ICardSelector.hpp"

#include <memory>
#include <string>

namespace cardmultigame::entities::decks
{
    class CreateCardDeck
    {
        std::shared_ptr<technical::rangens::ICardSelector> _selectedCardSelector;

    public:
        CreateCardDeck();

        // Return shared_ptr<CardDeck> — C# CardDeck is a reference type; the deck lives inside the
        // GameState bag and draws must mutate the shared instance (reference semantics preserved).
        std::shared_ptr<CardDeck> FromGivenCards(const std::string& cardsInDeck);
        std::shared_ptr<CardDeck> Simple9ToAWith4Colours();
        std::shared_ptr<CardDeck> Simple2ToAWith4Colours();
        std::shared_ptr<CardDeck> Empty();

        // Setter to change the default random generator.
        void SetCardSelector(std::shared_ptr<technical::rangens::ICardSelector> selector);
    };
}
