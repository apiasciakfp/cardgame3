package com.cardmultigame.usecases.gameconditions;

import com.cardmultigame.entities.gamestates.GameState;

public interface IGameCondition {
    void checkAndUpdate(GameState gameState);
}
