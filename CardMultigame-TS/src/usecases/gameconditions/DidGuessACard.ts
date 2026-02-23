import { GameState } from "../../entities/gamestates/GameState.js";
import * as ModifyGameState from "../influencestate/ModifyGameState.js";
import { IGameCondition } from "./IGameCondition.js";

/**
 * If there exists a 'Guess' key in the gameState AND the value is true,
 * declare game has been won.
 */
export class DidGuessACard implements IGameCondition {
  checkAndUpdate(currentGameState: GameState): void {
    const result = currentGameState.get("Guess");

    if (result !== null && result !== undefined) {
      const isGameWon = result as boolean;
      if (isGameWon) {
        ModifyGameState.declareGameToBeWon(currentGameState);
      }
    }
  }
}
