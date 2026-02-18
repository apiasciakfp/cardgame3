package com.cardmultigame.entities.gamestates;

import com.cardmultigame.entities.decks.CardDeck;
import com.cardmultigame.entities.decks.CreateCardDeck;

public class CreateGameState {

    public GameState withModifications(GameState stateModifier, CardDeck deck) {
        CardDeck deck2 = sanitizeDeck(deck);
        GameState stateModifier2 = sanitizeState(stateModifier);

        GameState constructedState = defaultState();
        for (var kvPair : stateModifier2.entrySet()) {
            constructedState.put(kvPair.getKey(), kvPair.getValue());
        }

        constructedState.put(GameStateKeys.CardDeck, deck2);
        return constructedState;
    }

    public GameState defaultsPlusDeck(CardDeck deck) {
        GameState constructedState = defaultState();
        constructedState.put(GameStateKeys.CardDeck, deck);
        return constructedState;
    }

    public GameState defaultsWithFullDeck() {
        GameState constructedState = defaultState();
        constructedState.put(GameStateKeys.CardDeck, new CreateCardDeck().simple2ToAWith4Colours());
        return constructedState;
    }

    public GameState defaultState() {
        GameState state = new GameState();
        state.put(GameStateKeys.CardDeck, new CreateCardDeck().empty());
        state.put(GameStateKeys.CurrentTurn, 0);
        state.put(GameStateKeys.MaxTurns, 0);
        state.put(GameStateKeys.IsGameLost, false);
        state.put(GameStateKeys.IsGameWon, false);
        return state;
    }

    private GameState sanitizeState(GameState stateModifier) {
        if (stateModifier == null)
            return new GameState();
        else
            return stateModifier;
    }

    private CardDeck sanitizeDeck(CardDeck deck) {
        if (deck == null)
            return new CreateCardDeck().empty();
        else
            return deck;
    }
}
