package com.cardmultigame.gamemanagers.selectedrules.creationcommands;

import com.cardmultigame.gamemanagers.GameManagerInternalsBuilder;

public interface ICreateGameRulesCommand {
    boolean shouldReactTo(String outerCommandName);
    void changeGameRuleset(GameManagerInternalsBuilder builder, String parameters);
}
