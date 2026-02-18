package com.cardmultigame.gamemanagers.selectedrules.creationcommands;

import com.cardmultigame.gamemanagers.GameManagerInternalsBuilder;
import com.cardmultigame.usecases.cardcomparison.BlackRedColourOnlyComparisonStrategy;

public class GameVariant implements ICreateGameRulesCommand {
    private String identifier = "GameVariant";

    @Override
    public void changeGameRuleset(GameManagerInternalsBuilder builder, String parameters) {
        builder.setCardComparisonStrategy(new BlackRedColourOnlyComparisonStrategy());
    }

    @Override
    public boolean shouldReactTo(String outerCommandName) {
        return identifier.toLowerCase().equals(outerCommandName.toLowerCase());
    }
}
