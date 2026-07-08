#include "entities/decks/CardDeck.hpp"

#include <algorithm>

namespace cardmultigame::entities::decks
{
    CardDeck::CardDeck(std::shared_ptr<technical::rangens::ICardSelector> selector, std::vector<std::shared_ptr<cards::Card>> cards)
        : _selector(std::move(selector)), _cards(std::move(cards))
    {
    }

    std::vector<std::shared_ptr<cards::Card>>& CardDeck::AllCards()
    {
        return _cards;
    }

    int CardDeck::CardsLeft() const
    {
        return static_cast<int>(_cards.size());
    }

    std::shared_ptr<cards::Card> CardDeck::DrawRandomCard()
    {
        std::shared_ptr<cards::Card> drawn = _selector->DrawCard(_cards);

        // Erase the exact drawn pointer (identity), mirroring C# List.Remove on a reference type.
        const auto at = std::find(_cards.begin(), _cards.end(), drawn);
        if (at != _cards.end())
        {
            _cards.erase(at);
        }

        return drawn;
    }

    std::shared_ptr<cards::Card> CardDeck::DrawLastAddedCard()
    {
        std::shared_ptr<cards::Card> drawn = _cards[_cards.size() - 1];

        const auto at = std::find(_cards.begin(), _cards.end(), drawn);
        if (at != _cards.end())
        {
            _cards.erase(at);
        }

        return drawn;
    }

    void CardDeck::AddASingleCard(std::shared_ptr<cards::Card> card)
    {
        _cards.push_back(std::move(card));
    }

    std::string CardDeck::ToString() const
    {
        std::string cardFaces;
        for (const auto& card : _cards)
        {
            cardFaces += "||" + card->ToString(); // leading "||" preserved (WART-4)
        }
        return "Deck: " + cardFaces;
    }
}
