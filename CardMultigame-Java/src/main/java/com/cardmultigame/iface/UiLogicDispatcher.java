package com.cardmultigame.iface;

import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.gamemanagers.CreateGameManager;
import com.cardmultigame.gamemanagers.GameManager;
import java.util.stream.Collectors;

public class UiLogicDispatcher {
    private GameManager gameManager;

    public UiLogicDispatcher() {
        gameManager = new CreateGameManager().empty();
    }

    public void doStuff(String orders) {
        gameManager.executeOrders(orders);
    }

    public void setupGame(String orders) {
        gameManager = new CreateGameManager().defaultsWithOrders(orders);
    }

    public String displayCurrentState() {
        GameState currentState = gameManager.currentState();
        return currentState.entrySet().stream()
            .map(Object::toString)
            .collect(Collectors.joining(";" + System.lineSeparator()));
    }
}
