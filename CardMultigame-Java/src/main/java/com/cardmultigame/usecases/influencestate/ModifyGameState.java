package com.cardmultigame.usecases.influencestate;

import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.entities.gamestates.GameStateKeys;

/**
 * STATELESS FOREVER. Commands (functions) over a Dictionary ONLY.
 * Commands change the internal state, they do not retrieve anything.
 *
 * This is a hint of 'C' in CQS.
 */
public final class ModifyGameState {
    private ModifyGameState() {}

    public static void addTurn(GameState currentGameState) {
        Integer currentTurn = (Integer) currentGameState.get(GameStateKeys.CurrentTurn);
        currentGameState.put(GameStateKeys.CurrentTurn, currentTurn + 1);
    }

    public static void declareGameToBeLost(GameState currentGameState) {
        currentGameState.put(GameStateKeys.IsGameLost, true);
    }

    public static void declareGameToBeWon(GameState currentGameState) {
        currentGameState.put(GameStateKeys.IsGameWon, true);
    }
}
