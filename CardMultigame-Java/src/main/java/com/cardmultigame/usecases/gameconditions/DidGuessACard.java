package com.cardmultigame.usecases.gameconditions;

import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.usecases.influencestate.ModifyGameState;

/**
 * If there exists a 'Guess' key in the gameState AND the value is true,
 * declare game has been won.
 */
public class DidGuessACard implements IGameCondition {

    @Override
    public void checkAndUpdate(GameState currentGameState) {
        Object result = currentGameState.get("Guess");

        if (result != null) {
            boolean isGameWon = (Boolean) result;
            if (isGameWon) {
                ModifyGameState.declareGameToBeWon(currentGameState);
            }
        }
    }
}
