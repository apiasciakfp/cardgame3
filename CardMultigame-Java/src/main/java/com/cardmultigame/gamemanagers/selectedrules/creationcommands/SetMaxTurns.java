package com.cardmultigame.gamemanagers.selectedrules.creationcommands;

import com.cardmultigame.gamemanagers.GameManagerInternalsBuilder;

public class SetMaxTurns implements ICreateGameRulesCommand {
    private String identifier = "SetMaxTurns";

    @Override
    public void changeGameRuleset(GameManagerInternalsBuilder builder, String parameters) {
        try {
            int maxTurns = Integer.parseInt(parameters.trim());
            builder.setMaxTurns(maxTurns);
        } catch (NumberFormatException e) {
            // C# TryParse silently ignores parse failures
        }
    }

    @Override
    public boolean shouldReactTo(String outerCommandName) {
        return identifier.toLowerCase().equals(outerCommandName.toLowerCase());
    }
}
