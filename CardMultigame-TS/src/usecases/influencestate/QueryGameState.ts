import { CardDeck } from "../../entities/decks/CardDeck.js";
import { GameState } from "../../entities/gamestates/GameState.js";
import { GameStateKeys } from "../../entities/gamestates/GameStateKeys.js";

/**
 * STATELESS FOREVER. Queries over a Dictionary ONLY.
 * Queries do not, ever, change the internal state at all. They are automatically safe.
 *
 * This is a hint of 'Q' in CQS.
 */
export function maximumTurns(currentState: GameState): number {
  const value = currentState.get(GameStateKeys.MaxTurns);
  if (value === null || value === undefined)
    throw new Error("Current turn cannot be a null");
  return value as number;
}

export function isGameWon(currentState: GameState): boolean {
  return currentState.get(GameStateKeys.IsGameWon) as boolean;
}

export function isGameLost(currentState: GameState): boolean {
  return currentState.get(GameStateKeys.IsGameLost) as boolean;
}

export function isGameFinished(currentState: GameState): boolean {
  return isGameWon(currentState) || isGameLost(currentState);
}

export function currentTurn(currentState: GameState): number {
  const value = currentState.get(GameStateKeys.CurrentTurn);
  if (value === null || value === undefined)
    throw new Error("Current turn cannot be a null");
  return value as number;
}

export function amountOfCardsLeft(currentState: GameState): number {
  return extractCardDeck(currentState).cardsLeft();
}

export function gameUndergoing(currentState: GameState): string {
  if (currentState.get(GameStateKeys.IsGameWon) as boolean) return "Victory";
  else if (currentState.get(GameStateKeys.IsGameLost) as boolean)
    return "Defeat";
  else return "Undergoing";
}

export function extractCardDeck(currentState: GameState): CardDeck {
  return currentState.get(GameStateKeys.CardDeck) as CardDeck;
}
