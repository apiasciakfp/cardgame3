package com.cardmultigame.usecases.gameactions;

import java.util.ArrayList;
import java.util.List;

public class CreateGameActions {

    public List<IGameAction> havingOrders(String actionsToPerform) {
        String[] tokens = actionsToPerform.split("\\s+");

        List<IGameAction> actions = new ArrayList<>();
        for (String token : tokens) {
            String sanitized = token.replace(",", "");

            if (sanitized.equals("drawSingleCard")) actions.add(new DrawSingleCardAction());
            if (sanitized.equals("addQH")) actions.add(new AddQueenOfHeartsToDeck());
            if (sanitized.equals("add10cOrDraw")) actions.add(new Add10COrDrawACard());
        }

        return actions;
    }
}
