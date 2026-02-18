package com.cardmultigame.entities.games;

import com.cardmultigame.entities.decks.CardDeck;
import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.usecases.cardcomparison.ICardComparisonStrategy;
import com.cardmultigame.usecases.gameactions.IGameAction;
import com.cardmultigame.usecases.gameconditions.IGameCondition;
import java.util.List;

public interface IGameImplementation {
    String title();
    CardDeck cardDeck();
    List<IGameAction> availableActions();
    List<IGameCondition> victoryConditions();
    List<IGameCondition> gameStopConditions();
    GameState initialGameState();
    ICardComparisonStrategy cardComparisonStrategy();
}
