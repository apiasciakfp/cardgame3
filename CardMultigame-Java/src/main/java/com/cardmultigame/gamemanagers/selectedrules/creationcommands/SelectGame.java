package com.cardmultigame.gamemanagers.selectedrules.creationcommands;

import com.cardmultigame.entities.games.GuessACardGame;
import com.cardmultigame.entities.games.IGameImplementation;
import com.cardmultigame.gamemanagers.GameManagerInternalsBuilder;

public class SelectGame implements ICreateGameRulesCommand {
    private String identifier = "Play";

    @Override
    public void changeGameRuleset(GameManagerInternalsBuilder builder, String parameters) {
        IGameImplementation gameImpl = selectGameImplementation(parameters);

        builder.setName(gameImpl.title());
        builder.setDeck(gameImpl.cardDeck());
        builder.setAvailableActions(gameImpl.availableActions());
        builder.setVictoryConditions(gameImpl.victoryConditions());
        builder.setGameStopConditions(gameImpl.gameStopConditions());
        builder.setInitialGameState(gameImpl.initialGameState());
        builder.setCardComparisonStrategy(gameImpl.cardComparisonStrategy());
    }

    @Override
    public boolean shouldReactTo(String outerCommandName) {
        return identifier.toLowerCase().equals(outerCommandName.toLowerCase());
    }

    private static IGameImplementation selectGameImplementation(String parameters) {
        IGameImplementation gameImpl = null;
        if (parameters.toLowerCase().equals("guessacard")) {
            gameImpl = new GuessACardGame();
        }

        if (gameImpl == null)
            throw new IllegalArgumentException(
                "Either the game is not registered in factory or game identifier has a typo. Got: " + parameters);

        return gameImpl;
    }
}
