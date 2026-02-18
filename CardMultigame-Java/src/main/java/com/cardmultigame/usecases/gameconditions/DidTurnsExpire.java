package com.cardmultigame.usecases.gameconditions;

import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.usecases.influencestate.ModifyGameState;
import com.cardmultigame.usecases.influencestate.QueryGameState;

/**
 * If currentTurn >= maxTurns: declare game has been lost.
 */
public class DidTurnsExpire implements IGameCondition {

    @Override
    public void checkAndUpdate(GameState currentGameState) {
        int currentTurn = QueryGameState.currentTurn(currentGameState);
        int maxTurns = QueryGameState.maximumTurns(currentGameState);

        if (currentTurn >= maxTurns) {
            ModifyGameState.declareGameToBeLost(currentGameState);
        }
    }
}
