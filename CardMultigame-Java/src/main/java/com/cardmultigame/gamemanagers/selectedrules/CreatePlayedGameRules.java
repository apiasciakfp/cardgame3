package com.cardmultigame.gamemanagers.selectedrules;

import com.cardmultigame.usecases.cardcomparison.CreateCardComparisonStrategy;
import com.cardmultigame.usecases.cardcomparison.ICardComparisonStrategy;
import com.cardmultigame.usecases.gameactions.IGameAction;
import com.cardmultigame.usecases.gameconditions.IGameCondition;
import java.util.ArrayList;
import java.util.List;

public class CreatePlayedGameRules {
    private String defaultGameName = "No game selected";
    private List<IGameAction> defaultActions = new ArrayList<>();
    private List<IGameCondition> defaultVictories = new ArrayList<>();
    private List<IGameCondition> defaultGameStops = new ArrayList<>();
    private ICardComparisonStrategy defaultCardComparators = new CreateCardComparisonStrategy().none();

    public PlayedGameRules empty() {
        return new PlayedGameRules(defaultGameName, defaultActions, defaultVictories, defaultGameStops, defaultCardComparators);
    }

    public PlayedGameRules withModifications(String gameName, List<IGameAction> actions, List<IGameCondition> victories,
                                             List<IGameCondition> gameStops, ICardComparisonStrategy compareCards) {
        String selectedName = defaultGameName;
        List<IGameAction> selectedActions = defaultActions;
        List<IGameCondition> selectedVictories = defaultVictories;
        List<IGameCondition> selectedGameStops = defaultGameStops;
        ICardComparisonStrategy selectedCardComparators = defaultCardComparators;

        if (gameName != null) selectedName = gameName;
        if (actions != null) selectedActions = actions;
        if (victories != null) selectedVictories = victories;
        if (gameStops != null) selectedGameStops = gameStops;
        if (compareCards != null) selectedCardComparators = compareCards;

        return new PlayedGameRules(selectedName, selectedActions, selectedVictories, selectedGameStops, selectedCardComparators);
    }
}
