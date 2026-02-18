package com.cardmultigame;

import com.cardmultigame.entities.cards.Card;
import com.cardmultigame.entities.cards.CreateCards;
import com.cardmultigame.entities.decks.CardDeck;
import com.cardmultigame.entities.decks.CreateCardDeck;
import com.cardmultigame.technical.parsers.ParsedOrder;
import com.cardmultigame.technical.parsers.SelectedParser;
import com.cardmultigame.technical.rangens.AlwaysFirstSelector;
import com.cardmultigame.technical.rangens.AlwaysLastSelector;
import com.cardmultigame.entities.games.GuessACardGame;
import com.cardmultigame.usecases.cardcomparison.*;
import org.junit.jupiter.api.Test;
import java.util.ArrayList;
import java.util.List;
import static org.assertj.core.api.Assertions.assertThat;

class Batch100Test {

    @Test
    void t108_letsPrepareTheStrategyForTheFuture() {
        // Given - nothing
        // When
        ICardComparisonStrategy selectedStrategy = new GuessACardGame().cardComparisonStrategy();

        // Then
        assertThat(selectedStrategy instanceof StrictCardComparisonStrategy).isTrue();
    }

    @Test
    void t101_strategyBasics() {
        Card card1 = new Card("J", "H");
        Card identicalCard = new Card("J", "H");
        Card differentCard = new Card("K", "H");

        boolean areTheSameWithIdentical = new StrictCardComparisonStrategy().areTheSame(card1, identicalCard);
        boolean areTheSameWithDifferent = new StrictCardComparisonStrategy().areTheSame(card1, differentCard);

        assertThat(areTheSameWithIdentical).isTrue();
        assertThat(areTheSameWithDifferent).isFalse();
    }

    @Test
    void t102_implementYourOwnStrategy() {
        Card card1 = new Card("J", "H");
        Card identicalCard = new Card("2", "H");
        Card differentCard = new Card("J", "D");

        boolean areTheSameWithIdentical = new ColourCardComparisonStrategy().areTheSame(card1, identicalCard);
        boolean areTheSameWithDifferent = new ColourCardComparisonStrategy().areTheSame(card1, differentCard);

        assertThat(areTheSameWithIdentical).isTrue();
        assertThat(areTheSameWithDifferent).isFalse();
    }

    @Test
    void t103_implementTheBlackRedStrategy() {
        Card reference = new Card("2", "H");
        Card identical1 = new Card("2", "H");
        Card identical2 = new Card("7", "D");
        Card different1 = new Card("2", "S");
        Card different2 = new Card("Q", "C");

        assertThat(new BlackRedColourOnlyComparisonStrategy().areTheSame(reference, identical1)).isTrue();
        assertThat(new BlackRedColourOnlyComparisonStrategy().areTheSame(reference, identical2)).isTrue();
        assertThat(new BlackRedColourOnlyComparisonStrategy().areTheSame(reference, different1)).isFalse();
        assertThat(new BlackRedColourOnlyComparisonStrategy().areTheSame(reference, different2)).isFalse();
    }

    @Test
    void t104_powerOfPolymorphism() {
        Card card1 = new Card("J", "H");
        Card card2 = new Card("A", "H");

        ICardComparisonStrategy strategy;

        strategy = new StrictCardComparisonStrategy();
        assertThat(strategy.areTheSame(card1, card2)).isFalse();

        strategy = new ColourCardComparisonStrategy();
        assertThat(strategy.areTheSame(card1, card2)).isTrue();

        strategy = new RankCardComparisonStrategy();
        assertThat(strategy.areTheSame(card1, card2)).isFalse();

        strategy = new BlackRedColourOnlyComparisonStrategy();
        assertThat(strategy.areTheSame(card1, card2)).isTrue();
    }

    @Test
    void t105_factoryMethod_oneStrategyOnly() {
        Card card1 = new Card("J", "H");
        Card card2 = new Card("A", "H");

        ICardComparisonStrategy strategy = new CreateCardComparisonStrategy().create("colour");
        boolean areTheSame = strategy.areTheSame(card1, card2);

        assertThat(areTheSame).isTrue();
    }

    @Test
    void t106_factoryMethod_allStrategies() {
        Card card1 = new Card("J", "H");
        Card card2 = new Card("A", "H");

        ICardComparisonStrategy strategy;

        strategy = new CreateCardComparisonStrategy().create("strict");
        assertThat(strategy.areTheSame(card1, card2)).isFalse();

        strategy = new CreateCardComparisonStrategy().create("colour");
        assertThat(strategy.areTheSame(card1, card2)).isTrue();

        strategy = new CreateCardComparisonStrategy().create("rank");
        assertThat(strategy.areTheSame(card1, card2)).isFalse();

        strategy = new CreateCardComparisonStrategy().create("blackred");
        assertThat(strategy.areTheSame(card1, card2)).isTrue();
    }

    @Test
    void t107_nullObjectWeAllLove() {
        Card card1 = new Card("J", "H");
        Card card2 = new Card("A", "H");

        List<ICardComparisonStrategy> strategies = List.of(
            new CreateCardComparisonStrategy().create("THIS IS A TYPO!"),
            new CreateCardComparisonStrategy().create(""),
            new CreateCardComparisonStrategy().create("al/fdkafklfhflsdhflhffhfh"),
            new CreateCardComparisonStrategy().create("f;lff;kklfs;df"),
            new CreateCardComparisonStrategy().create("don't else-if those cases please...")
        );

        for (ICardComparisonStrategy strategy : strategies) {
            assertThat(strategy.areTheSame(card1, card2)).isFalse();
        }
    }

    @Test
    void t109_cardDeckNeedsDifferentCreationWays() {
        int cardsBetween2A = 13;
        int cardColours = 4;
        int totalCards = cardsBetween2A * cardColours;

        Card lowCard = new Card("2", "C");
        Card highCard = new Card("K", "H");

        CardDeck deck = new CreateCardDeck().simple2ToAWith4Colours();
        List<Card> allCards = deck.allCards();

        boolean foundSmall = false;
        boolean foundLarge = false;

        for (Card card : allCards) {
            if (new StrictCardComparisonStrategy().areTheSame(card, lowCard)) foundSmall = true;
            if (new StrictCardComparisonStrategy().areTheSame(card, highCard)) foundLarge = true;
        }

        assertThat(foundSmall).isTrue();
        assertThat(foundLarge).isTrue();
    }

    @Test
    void t110_parsers_ofCourseParsers() {
        List<ParsedOrder> ordersExpected;
        String ordersString;
        List<ParsedOrder> ordersReceived;

        // Case1: ';' as main delimiter, ',' as second.
        ordersExpected = List.of(
            new ParsedOrder("Play", "GuessACard"),
            new ParsedOrder("SetDeck", "JH, QH, KH"),
            new ParsedOrder("StartGame", ""),
            new ParsedOrder("Guess", "JH"),
            new ParsedOrder("Guess", "QH")
        );
        ordersString = "Play GuessACard; SetDeck JH, QH, KH; StartGame; Guess JH; Guess QH";
        ordersReceived = new SelectedParser().properlyParse(ordersString);
        for (int i = 0; i < ordersExpected.size(); i++) {
            assertThat(ordersReceived.get(i)).isEqualTo(ordersExpected.get(i));
        }

        // Case2: ',' as main delimiter, ';' as second.
        ordersExpected = List.of(
            new ParsedOrder("Play", "GuessACard"),
            new ParsedOrder("SetDeck", "JH; QH; KH"),
            new ParsedOrder("StartGame", ""),
            new ParsedOrder("Guess", "JH"),
            new ParsedOrder("Guess", "QH")
        );
        ordersString = "Play GuessACard, SetDeck JH; QH; KH, StartGame, Guess JH, Guess QH";
        ordersReceived = new SelectedParser().properlyParse(ordersString);
        for (int i = 0; i < ordersExpected.size(); i++) {
            assertThat(ordersReceived.get(i)).isEqualTo(ordersExpected.get(i));
        }

        // Case3: '-' as main delimiter, ',' as second.
        ordersExpected = List.of(
            new ParsedOrder("Play", "GuessACard"),
            new ParsedOrder("SetDeck", "JH, QH, KH"),
            new ParsedOrder("StartGame", ""),
            new ParsedOrder("Guess", "JH"),
            new ParsedOrder("Guess", "QH")
        );
        ordersString = "Play GuessACard - SetDeck JH, QH, KH - StartGame - Guess JH - Guess QH";
        ordersReceived = new SelectedParser().properlyParse(ordersString);
        for (int i = 0; i < ordersExpected.size(); i++) {
            assertThat(ordersReceived.get(i)).isEqualTo(ordersExpected.get(i));
        }
    }

    @Test
    void t111_cardDeckCanHaveConfiguredRandomGenerator_first() {
        // Given, Expected
        AlwaysFirstSelector selector = new AlwaysFirstSelector();
        List<Card> expectedCards = new CreateCards().createCollection("9H, 10H, 9C, 10C, AD");

        List<Card> copiedList = new ArrayList<>(expectedCards);
        CardDeck deck = new CardDeck(selector, copiedList);

        // When
        List<Card> actualCards = new ArrayList<>();
        for (int i = 0; i < 5; i++) {
            actualCards.add(deck.drawRandomCard());
        }

        // Then
        for (int i = 0; i < 5; i++) {
            assertThat(expectedCards.get(i).colour().equals(actualCards.get(i).colour())).isTrue();
            assertThat(expectedCards.get(i).rank().equals(actualCards.get(i).rank())).isTrue();
        }
    }

    @Test
    void t112_cardDeckCanHaveConfiguredRandomGenerator_last() {
        // Given, Expected
        AlwaysLastSelector selector = new AlwaysLastSelector();
        List<Card> expectedCards = new CreateCards().createCollection("9H, 10H, 9C, 10C, AD");

        List<Card> copiedList = new ArrayList<>(expectedCards);
        CardDeck deck = new CardDeck(selector, copiedList);

        // When
        List<Card> actualCards = new ArrayList<>();
        for (int i = 0; i < 5; i++) {
            actualCards.add(deck.drawRandomCard());
        }

        // Then
        for (int i = 0; i < 5; i++) {
            assertThat(expectedCards.get(4 - i).colour().equals(actualCards.get(i).colour())).isTrue();
            assertThat(expectedCards.get(4 - i).rank().equals(actualCards.get(i).rank())).isTrue();
        }
    }

    @Test
    void t113_cardDeckFactory_canReconfigureRandomGenerator() {
        // Given
        String inputCardSigils = "JS, QH, KD, AC";

        // Expected
        List<Card> expectedCards = new CreateCards().createCollection(inputCardSigils);

        // Given: look at this CLOSELY
        CreateCardDeck creator = new CreateCardDeck();

        creator.setCardSelector(new AlwaysFirstSelector());
        CardDeck deckWithAlwaysFirst = creator.fromGivenCards(inputCardSigils);

        // When
        List<Card> actualFirstCards = new ArrayList<>();
        for (int i = 0; i < 4; i++) {
            actualFirstCards.add(deckWithAlwaysFirst.drawRandomCard());
        }

        // Then
        for (int i = 0; i < 4; i++) {
            assertThat(expectedCards.get(i).colour().equals(actualFirstCards.get(i).colour())).isTrue();
            assertThat(expectedCards.get(i).rank().equals(actualFirstCards.get(i).rank())).isTrue();
        }

        // Given again
        creator.setCardSelector(new AlwaysLastSelector());
        CardDeck deckWithAlwaysLast = creator.fromGivenCards(inputCardSigils);

        // When
        List<Card> actualLastCards = new ArrayList<>();
        for (int i = 0; i < 4; i++) {
            actualLastCards.add(deckWithAlwaysLast.drawRandomCard());
        }

        // Then
        for (int i = 0; i < 4; i++) {
            assertThat(expectedCards.get(3 - i).colour().equals(actualLastCards.get(i).colour())).isTrue();
            assertThat(expectedCards.get(3 - i).rank().equals(actualLastCards.get(i).rank())).isTrue();
        }
    }
}
