package com.cardmultigame.gamemanagers.selectedrules.creationcommands;

import com.cardmultigame.entities.decks.CardDeck;
import com.cardmultigame.entities.decks.CreateCardDeck;
import com.cardmultigame.gamemanagers.GameManagerInternalsBuilder;

public class SetDeck implements ICreateGameRulesCommand {
    private String identifier = "SetDeck";

    @Override
    public void changeGameRuleset(GameManagerInternalsBuilder builder, String parameters) {
        CardDeck deck = new CreateCardDeck().fromGivenCards(parameters);
        builder.setDeck(deck);
    }

    @Override
    public boolean shouldReactTo(String outerCommandName) {
        return identifier.toLowerCase().equals(outerCommandName.toLowerCase());
    }
}
