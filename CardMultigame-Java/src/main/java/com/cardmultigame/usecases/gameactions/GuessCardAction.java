package com.cardmultigame.usecases.gameactions;

import com.cardmultigame.entities.cards.Card;
import com.cardmultigame.entities.cards.CreateCards;
import com.cardmultigame.entities.decks.CardDeck;
import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.gamemanagers.selectedrules.PlayedGameRules;
import com.cardmultigame.usecases.cardcomparison.ICardComparisonStrategy;
import com.cardmultigame.usecases.influencestate.ModifyGameState;
import com.cardmultigame.usecases.influencestate.QueryGameState;

public class GuessCardAction implements IGameAction {
    private String identifier = "Guess";

    @Override
    public void changeGameState(GameState currentGameState, PlayedGameRules rules, String orderParams) {
        Card candidate = new CreateCards().createSingle(orderParams);

        CardDeck deck = QueryGameState.extractCardDeck(currentGameState);
        Card actuallyDrawnCard = deck.drawRandomCard();

        ICardComparisonStrategy comparator = rules.cardComparator();

        boolean areTheSame = comparator.areTheSame(candidate, actuallyDrawnCard);

        if (areTheSame) currentGameState.put(identifier, true);
        else currentGameState.put(identifier, false);

        ModifyGameState.addTurn(currentGameState);
    }

    @Override
    public boolean shouldReactTo(String orderName) {
        return identifier.toLowerCase().equals(orderName.toLowerCase());
    }
}
