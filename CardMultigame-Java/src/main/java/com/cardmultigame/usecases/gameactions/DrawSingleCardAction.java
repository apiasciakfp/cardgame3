package com.cardmultigame.usecases.gameactions;

import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.gamemanagers.selectedrules.PlayedGameRules;
import com.cardmultigame.usecases.influencestate.QueryGameState;

public class DrawSingleCardAction implements IGameAction {

    @Override
    public void changeGameState(GameState currentGameState, PlayedGameRules gameRules, String orderParams) {
        QueryGameState.extractCardDeck(currentGameState).drawRandomCard();

        if (QueryGameState.amountOfCardsLeft(currentGameState) == 0)
            currentGameState.put("Guess", true);
    }

    @Override
    public boolean shouldReactTo(String item) {
        throw new UnsupportedOperationException();
    }
}
