package com.cardmultigame.gamemanagers.selectedrules;

import com.cardmultigame.gamemanagers.GameManagerInternalsBuilder;
import com.cardmultigame.gamemanagers.selectedrules.creationcommands.*;
import com.cardmultigame.technical.parsers.ParsedOrder;
import java.util.List;

public class CreateGameStructure {
    private List<ICreateGameRulesCommand> commands;

    public CreateGameStructure() {
        commands = registerAvailableCreationCommands();
    }

    public GameManagerInternalsBuilder buildRulesAndInitialState(List<ParsedOrder> orders) {
        GameManagerInternalsBuilder builder = new GameManagerInternalsBuilder();
        for (ParsedOrder order : orders) {
            for (ICreateGameRulesCommand orderUser : commands) {
                if (orderUser.shouldReactTo(order.command())) {
                    orderUser.changeGameRuleset(builder, order.params());
                }
            }
        }

        return builder;
    }

    private List<ICreateGameRulesCommand> registerAvailableCreationCommands() {
        return List.of(new SelectGame(), new SetDeck(), new SetMaxTurns(), new GameVariant());
    }
}
