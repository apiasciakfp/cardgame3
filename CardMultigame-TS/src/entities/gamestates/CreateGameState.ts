import { CardDeck } from "../decks/CardDeck.js";
import { CreateCardDeck } from "../decks/CreateCardDeck.js";
import { GameState } from "./GameState.js";
import { GameStateKeys } from "./GameStateKeys.js";

export class CreateGameState {
  withModifications(
    stateModifier: GameState | null,
    deck: CardDeck | null
  ): GameState {
    const deck2 = this.sanitizeDeck(deck);
    const stateModifier2 = this.sanitizeState(stateModifier);

    const constructedState = this.defaultState();
    for (const [key, value] of stateModifier2) {
      constructedState.set(key, value);
    }

    constructedState.set(GameStateKeys.CardDeck, deck2);
    return constructedState;
  }

  defaultsPlusDeck(deck: CardDeck): GameState {
    const constructedState = this.defaultState();
    constructedState.set(GameStateKeys.CardDeck, deck);
    return constructedState;
  }

  defaultsWithFullDeck(): GameState {
    const constructedState = this.defaultState();
    constructedState.set(
      GameStateKeys.CardDeck,
      new CreateCardDeck().simple2ToAWith4Colours()
    );
    return constructedState;
  }

  defaultState(): GameState {
    const state = new GameState();
    state.set(GameStateKeys.CardDeck, new CreateCardDeck().empty());
    state.set(GameStateKeys.CurrentTurn, 0);
    state.set(GameStateKeys.MaxTurns, 0);
    state.set(GameStateKeys.IsGameLost, false);
    state.set(GameStateKeys.IsGameWon, false);
    return state;
  }

  private sanitizeState(stateModifier: GameState | null): GameState {
    if (stateModifier === null) return new GameState();
    return stateModifier;
  }

  private sanitizeDeck(deck: CardDeck | null): CardDeck {
    if (deck === null) return new CreateCardDeck().empty();
    return deck;
  }
}
