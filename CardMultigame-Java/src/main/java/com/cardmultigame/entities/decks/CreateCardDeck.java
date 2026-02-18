package com.cardmultigame.entities.decks;

import com.cardmultigame.entities.cards.Card;
import com.cardmultigame.entities.cards.CreateCards;
import com.cardmultigame.technical.rangens.ICardSelector;
import com.cardmultigame.technical.rangens.RandomCardSelector;
import java.util.ArrayList;
import java.util.List;

public class CreateCardDeck {
    private ICardSelector selectedCardSelector = new RandomCardSelector();

    public CardDeck fromGivenCards(String cardsInDeck) {
        List<Card> cards = new CreateCards().createCollection(cardsInDeck);
        return new CardDeck(selectedCardSelector, cards);
    }

    public CardDeck simple9ToAWith4Colours() {
        List<String> ranks = List.of("9", "10", "J", "Q", "K", "A");
        List<String> colours = List.of("S", "H", "D", "C");

        List<Card> cards = new ArrayList<>();
        for (String rank : ranks) {
            for (String colour : colours) {
                String cardPrototype = rank + colour;
                Card card = new CreateCards().createSingle(cardPrototype);
                cards.add(card);
            }
        }
        return new CardDeck(selectedCardSelector, cards);
    }

    public CardDeck simple2ToAWith4Colours() {
        List<String> ranks = List.of("2", "3", "4", "5", "6", "7", "8",
                "9", "10", "J", "Q", "K", "A");
        List<String> colours = List.of("S", "H", "D", "C");

        List<Card> cards = new ArrayList<>();
        for (String rank : ranks) {
            for (String colour : colours) {
                String cardPrototype = rank + colour;
                Card card = new CreateCards().createSingle(cardPrototype);
                cards.add(card);
            }
        }
        return new CardDeck(selectedCardSelector, cards);
    }

    public CardDeck empty() {
        return new CardDeck(selectedCardSelector, new ArrayList<>());
    }

    public void setCardSelector(ICardSelector selector) {
        this.selectedCardSelector = selector;
    }
}
