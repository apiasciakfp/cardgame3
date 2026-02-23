import { GameState } from "../../entities/gamestates/GameState.js";
import * as QueryGameState from "../influencestate/QueryGameState.js";
import * as ModifyGameState from "../influencestate/ModifyGameState.js";
import { IGameCondition } from "./IGameCondition.js";

/**
 * If currentTurn >= maxTurns: declare game has been lost.
 */
export class DidTurnsExpire implements IGameCondition {
  checkAndUpdate(currentGameState: GameState): void {
    const current = QueryGameState.currentTurn(currentGameState);
    const max = QueryGameState.maximumTurns(currentGameState);

    if (current >= max) {
      ModifyGameState.declareGameToBeLost(currentGameState);
    }
  }
}
