package com.cardmultigame.usecases.gameactions;

import com.cardmultigame.entities.cards.Card;
import com.cardmultigame.entities.decks.CardDeck;
import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.gamemanagers.selectedrules.PlayedGameRules;
import com.cardmultigame.usecases.influencestate.QueryGameState;

public class AddQueenOfHeartsToDeck implements IGameAction {

    @Override
    public void changeGameState(GameState currentGameState, PlayedGameRules gameRules, String orderParams) {
        CardDeck deck = QueryGameState.extractCardDeck(currentGameState);
        deck.addASingleCard(new Card("Q", "H"));
    }

    @Override
    public boolean shouldReactTo(String item) {
        throw new UnsupportedOperationException();
    }
}
