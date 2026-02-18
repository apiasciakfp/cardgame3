package com.cardmultigame.gamemanagers.selectedrules;

import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.usecases.cardcomparison.ICardComparisonStrategy;
import com.cardmultigame.usecases.gameactions.IGameAction;
import com.cardmultigame.usecases.gameconditions.IGameCondition;
import java.util.List;

public class PlayedGameRules {
    private String gameName;
    private List<IGameAction> actions;
    private List<IGameCondition> victoryConditions;
    private List<IGameCondition> gameStopConditions;
    private ICardComparisonStrategy cardComparator;

    public PlayedGameRules(String gameName, List<IGameAction> actions, List<IGameCondition> victories,
                           List<IGameCondition> gameStops, ICardComparisonStrategy compareCards) {
        this.gameName = gameName;
        this.actions = actions;
        this.victoryConditions = victories;
        this.gameStopConditions = gameStops;
        this.cardComparator = compareCards;
    }

    public ICardComparisonStrategy cardComparator() {
        return cardComparator;
    }

    public List<IGameAction> gameActions() { return actions; }
    public List<IGameCondition> victoryConditions() { return victoryConditions; }
    public List<IGameCondition> gameStopConditions() { return gameStopConditions; }
    public String gameName() { return gameName; }

    public void checkVictoryConditions(GameState currentGameState) {
        for (IGameCondition victory : victoryConditions) {
            victory.checkAndUpdate(currentGameState);
        }
    }

    public void checkGameStopConditions(GameState currentGameState) {
        for (IGameCondition stop : gameStopConditions) {
            stop.checkAndUpdate(currentGameState);
        }
    }
}
