package com.cardmultigame.usecases.influencestate;

import com.cardmultigame.entities.decks.CardDeck;
import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.entities.gamestates.GameStateKeys;

/**
 * STATELESS FOREVER. Queries over a Dictionary ONLY.
 * Queries do not, ever, change the internal state at all. They are automatically safe.
 *
 * This is a hint of 'Q' in CQS.
 */
public final class QueryGameState {
    private QueryGameState() {}

    public static int maximumTurns(GameState currentState) {
        Integer currentTurn = (Integer) currentState.get(GameStateKeys.MaxTurns);
        if (currentTurn == null) throw new IllegalArgumentException("Current turn cannot be a null");
        return currentTurn;
    }

    public static boolean isGameWon(GameState currentState) {
        return (boolean) currentState.get(GameStateKeys.IsGameWon);
    }

    public static boolean isGameLost(GameState currentState) {
        return (boolean) currentState.get(GameStateKeys.IsGameLost);
    }

    public static boolean isGameFinished(GameState currentState) {
        return isGameWon(currentState) || isGameLost(currentState);
    }

    public static int currentTurn(GameState currentState) {
        Integer currentTurn = (Integer) currentState.get(GameStateKeys.CurrentTurn);
        if (currentTurn == null) throw new IllegalArgumentException("Current turn cannot be a null");
        return currentTurn;
    }

    public static int amountOfCardsLeft(GameState currentState) {
        return extractCardDeck(currentState).cardsLeft();
    }

    public static String gameUndergoing(GameState currentState) {
        if ((boolean) currentState.get(GameStateKeys.IsGameWon)) return "Victory";
        else if ((boolean) currentState.get(GameStateKeys.IsGameLost)) return "Defeat";
        else return "Undergoing";
    }

    public static CardDeck extractCardDeck(GameState currentState) {
        return (CardDeck) currentState.get(GameStateKeys.CardDeck);
    }
}
