package com.cardmultigame.entities.decks;

import com.cardmultigame.entities.cards.Card;
import com.cardmultigame.technical.rangens.ICardSelector;
import com.cardmultigame.technical.rangens.RandomCardSelector;
import java.util.ArrayList;
import java.util.List;

public class CardDeck {
    private ICardSelector selector = new RandomCardSelector();
    private List<Card> cards = new ArrayList<>();

    public CardDeck(ICardSelector selector, List<Card> cards) {
        this.selector = selector;
        this.cards = cards;
    }

    public List<Card> allCards() { return cards; }
    public int cardsLeft() { return cards.size(); }

    public Card drawRandomCard() {
        Card drawn = selector.drawCard(cards);
        cards.remove(drawn);
        return drawn;
    }

    public Card drawLastAddedCard() {
        Card drawn = cards.get(cards.size() - 1);
        cards.remove(drawn);
        return drawn;
    }

    public void addASingleCard(Card card) {
        cards.add(card);
    }

    @Override
    public String toString() {
        String cardFaces = cards.stream()
                .map(Card::toString)
                .reduce("", (acc, card) -> acc + "||" + card);
        return "Deck: " + cardFaces;
    }
}
