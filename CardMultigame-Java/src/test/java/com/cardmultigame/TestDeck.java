package com.cardmultigame;

import com.cardmultigame.entities.cards.Card;
import com.cardmultigame.entities.cards.CreateCards;
import com.cardmultigame.entities.decks.CardDeck;
import com.cardmultigame.entities.decks.CreateCardDeck;
import com.cardmultigame.usecases.cardcomparison.StrictCardComparisonStrategy;
import org.junit.jupiter.api.Test;
import java.util.ArrayList;
import java.util.List;
import static org.assertj.core.api.Assertions.assertThat;

class TestDeck {

    @Test
    void drawCardFromDeck_randomly_5CardsUntil0Left() {
        // Given
        List<String> cardSigils = List.of("9H", "10H", "JH", "QH", "KH");
        String separator = ",";
        String cardsInDeck = String.join(separator, cardSigils);

        List<Card> cards = new CreateCards().createCollection(cardsInDeck);
        CardDeck deck = new CreateCardDeck().fromGivenCards(cardsInDeck);

        // Expecting
        int lengthInDeck = 0;
        int lengthOfDrawnCards = cards.size();

        // When
        List<Card> drawnCards = new ArrayList<>();
        for (int i = 0; i < cardSigils.size(); i++) {
            drawnCards.add(deck.drawRandomCard());
        }

        // Then
        List<Card> cardsRemaining = deck.allCards();

        assertThat(cardsRemaining.size() == lengthInDeck).isTrue();
        assertThat(drawnCards.size() == lengthOfDrawnCards).isTrue();
    }

    @Test
    void createDeck_withStandardCards9ToAWith4Colours() {
        // Given
        // Expecting
        int cardCountExpected = 24;

        // When
        CardDeck deck = new CreateCardDeck().simple9ToAWith4Colours();

        // Then
        List<Card> cardsReceived = deck.allCards();

        assertThat(cardsReceived.size() == cardCountExpected).isTrue();
    }

    @Test
    void createDeck_with3SetCards_inCommaFormat() {
        // Given
        List<String> cards = List.of("JH", "QH", "KH");
        String separator = ",";
        String cardsInDeck = String.join(separator, cards);

        // Expecting
        List<Card> cardsExpected = new CreateCards().createCollection(cardsInDeck);

        // When
        CardDeck deck = new CreateCardDeck().fromGivenCards(cardsInDeck);

        // Then
        List<Card> cardsReceived = deck.allCards();

        assertThat(cardsExpected.size() == cardsReceived.size()).isTrue();

        for (int i = 0; i < cardsExpected.size(); i++) {
            assertThat(new StrictCardComparisonStrategy().areTheSame(cardsExpected.get(i), cardsReceived.get(i))).isTrue();
        }
    }
}
