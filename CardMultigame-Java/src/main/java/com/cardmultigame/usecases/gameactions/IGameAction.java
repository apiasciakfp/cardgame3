package com.cardmultigame.usecases.gameactions;

import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.gamemanagers.selectedrules.PlayedGameRules;

public interface IGameAction {
    boolean shouldReactTo(String item);
    void changeGameState(GameState gameState, PlayedGameRules rules, String parameter);
}
