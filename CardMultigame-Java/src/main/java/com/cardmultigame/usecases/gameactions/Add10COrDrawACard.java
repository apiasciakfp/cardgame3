package com.cardmultigame.usecases.gameactions;

import com.cardmultigame.entities.cards.Card;
import com.cardmultigame.entities.decks.CardDeck;
import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.gamemanagers.selectedrules.PlayedGameRules;
import com.cardmultigame.usecases.influencestate.QueryGameState;

public class Add10COrDrawACard implements IGameAction {

    @Override
    public void changeGameState(GameState currentGameState, PlayedGameRules gameRules, String orderParams) {
        CardDeck deck = QueryGameState.extractCardDeck(currentGameState);

        if (QueryGameState.amountOfCardsLeft(currentGameState) % 2 == 0) {
            deck.addASingleCard(new Card("10", "C"));
        } else {
            deck.drawRandomCard();
        }
    }

    @Override
    public boolean shouldReactTo(String item) {
        throw new UnsupportedOperationException();
    }
}
