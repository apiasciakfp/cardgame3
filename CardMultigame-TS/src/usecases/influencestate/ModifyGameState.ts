import { GameState } from "../../entities/gamestates/GameState.js";
import { GameStateKeys } from "../../entities/gamestates/GameStateKeys.js";

/**
 * STATELESS FOREVER. Commands (functions) over a Dictionary ONLY.
 * Commands change the internal state, they do not retrieve anything.
 *
 * This is a hint of 'C' in CQS.
 */
export function addTurn(currentGameState: GameState): void {
  const currentTurn = currentGameState.get(
    GameStateKeys.CurrentTurn
  ) as number;
  currentGameState.set(GameStateKeys.CurrentTurn, currentTurn + 1);
}

export function declareGameToBeLost(currentGameState: GameState): void {
  currentGameState.set(GameStateKeys.IsGameLost, true);
}

export function declareGameToBeWon(currentGameState: GameState): void {
  currentGameState.set(GameStateKeys.IsGameWon, true);
}
