package com.cardmultigame;

import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.gamemanagers.CreateGameManager;
import com.cardmultigame.gamemanagers.GameManager;
import com.cardmultigame.usecases.influencestate.QueryGameState;
import org.junit.jupiter.api.Test;
import java.util.List;
import static org.assertj.core.api.Assertions.assertThat;

class TestGuessACard {

    @Test
    void directCardGuessingWorks_forThreeCardsDeck_failure() {
        // Given primitives
        List<String> cards = List.of("JH", "QH", "KH");
        String cardOutsideDeck = "2C";
        String secondSeparator = ",";
        String cardsInDeck = String.join(secondSeparator, cards);

        // Given
        String orders = "Play GuessACard; SetDeck " + cardsInDeck + "; SetMaxTurns 3; " +
            "Guess " + cardOutsideDeck + "; Guess " + cardOutsideDeck + "; Guess " + cardOutsideDeck;

        GameManager gm = new CreateGameManager().defaultsWithOrders(orders);

        // When
        gm.executeOrders(orders);
        GameState resultReceived = gm.currentState();

        // Then
        assertThat(QueryGameState.gameUndergoing(resultReceived).equals("Defeat")).isTrue();
        assertThat(QueryGameState.maximumTurns(resultReceived) == QueryGameState.currentTurn(resultReceived)).isTrue();
        assertThat(QueryGameState.amountOfCardsLeft(resultReceived) == 0).isTrue();
    }

    @Test
    void directCardGuessingWorks_forThreeCardsDeck_failure_diffSeparators() {
        // Given primitives
        List<String> cards = List.of("JH", "QH", "KH");
        String cardOutsideDeck = "2C";
        String secondSeparator = ";";
        String cardsInDeck = String.join(secondSeparator, cards);

        // Given
        String orders = "Play GuessACard, SetDeck " + cardsInDeck + ", SetMaxTurns 3, " +
            "Guess " + cardOutsideDeck + ", Guess " + cardOutsideDeck + ", Guess " + cardOutsideDeck;

        GameManager gm = new CreateGameManager().defaultsWithOrders(orders);

        // When
        gm.executeOrders(orders);
        GameState resultReceived = gm.currentState();

        // Then
        assertThat(QueryGameState.gameUndergoing(resultReceived).equals("Defeat")).isTrue();
        assertThat(QueryGameState.maximumTurns(resultReceived) == QueryGameState.currentTurn(resultReceived)).isTrue();
        assertThat(QueryGameState.amountOfCardsLeft(resultReceived) == 0).isTrue();
    }

    @Test
    void directCardGuessingWorks_forThreeCardsDeck_victory() {
        // Given primitives
        List<String> cards = List.of("JH", "QH", "KH");
        String cardInsideDeck = "JH";
        String secondSeparator = ",";
        String cardsInDeck = String.join(secondSeparator, cards);

        // Given
        String orders = "Play GuessACard; SetDeck " + cardsInDeck + "; SetMaxTurns 3; " +
            "Guess " + cardInsideDeck + "; Guess " + cardInsideDeck + "; Guess " + cardInsideDeck;

        GameManager gm = new CreateGameManager().defaultsWithOrders(orders);

        // When
        gm.executeOrders(orders);
        GameState resultReceived = gm.currentState();

        // Then
        assertThat(QueryGameState.gameUndergoing(resultReceived).equals("Victory")).isTrue();
    }

    @Test
    void cardRedBlackGuessingWorks_forThreeCardsOneColourDeck_missMissVictory() {
        // Given primitives
        List<String> cards = List.of("JH", "QH", "KH");
        String cardOutsideDeck = "2C";
        String cardInsideDeck = "2D";
        String secondSeparator = ",";
        String cardsInDeck = String.join(secondSeparator, cards);

        // Given
        String orders = "Play GuessACard; SetDeck " + cardsInDeck + "; GameVariant RedBlack; " +
            "Guess " + cardOutsideDeck + "; Guess " + cardOutsideDeck + "; Guess " + cardInsideDeck;

        GameManager gm = new CreateGameManager().defaultsWithOrders(orders);

        // When
        gm.executeOrders(orders);
        GameState resultReceived = gm.currentState();

        // Then
        assertThat(QueryGameState.gameUndergoing(resultReceived).equals("Victory")).isTrue();
    }
}
