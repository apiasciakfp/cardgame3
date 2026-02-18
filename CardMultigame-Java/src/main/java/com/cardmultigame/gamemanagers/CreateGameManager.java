package com.cardmultigame.gamemanagers;

import com.cardmultigame.entities.gamestates.CreateGameState;
import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.gamemanagers.selectedrules.CreateGameStructure;
import com.cardmultigame.gamemanagers.selectedrules.CreatePlayedGameRules;
import com.cardmultigame.gamemanagers.selectedrules.PlayedGameRules;
import com.cardmultigame.technical.parsers.ParsedOrder;
import com.cardmultigame.technical.parsers.SelectedParser;
import java.util.List;

public class CreateGameManager {

    public GameManager defaultsWithOrders(String orderString) {
        List<ParsedOrder> orders = new SelectedParser().properlyParse(orderString);

        GameManagerInternalsBuilder builder = new CreateGameStructure().buildRulesAndInitialState(orders);

        PlayedGameRules rules = builder.constructRuleset();
        GameState initialState = builder.constructGameState();

        return new GameManager(initialState, rules);
    }

    public GameManager empty() {
        GameState initialState = new CreateGameState().defaultState();
        PlayedGameRules rules = new CreatePlayedGameRules().empty();

        return new GameManager(initialState, rules);
    }
}
