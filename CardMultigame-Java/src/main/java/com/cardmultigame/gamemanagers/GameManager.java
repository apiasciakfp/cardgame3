package com.cardmultigame.gamemanagers;

import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.gamemanagers.selectedrules.PlayedGameRules;
import com.cardmultigame.technical.parsers.ParsedOrder;
import com.cardmultigame.technical.parsers.SelectedParser;
import com.cardmultigame.usecases.gameactions.IGameAction;
import com.cardmultigame.usecases.influencestate.QueryGameState;
import java.util.List;

public class GameManager {
    private GameState currentGameState;
    private PlayedGameRules gameRules;

    public GameManager(GameState initialState, PlayedGameRules rules) {
        this.currentGameState = initialState;
        this.gameRules = rules;
    }

    public void executeOrders(String orderString) {
        List<ParsedOrder> orders = new SelectedParser().properlyParse(orderString);

        for (ParsedOrder order : orders) {
            if (QueryGameState.isGameFinished(currentGameState)) return;

            for (IGameAction gameAction : gameRules.gameActions()) {
                if (gameAction.shouldReactTo(order.command())) {
                    gameAction.changeGameState(currentGameState, gameRules, order.params());

                    // CRITICAL: victory checked BEFORE game stop (load-bearing order)
                    gameRules.checkVictoryConditions(currentGameState);
                    gameRules.checkGameStopConditions(currentGameState);
                }
            }
        }
    }

    public GameState currentState() {
        return currentGameState;
    }
}
