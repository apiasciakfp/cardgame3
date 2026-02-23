import { GameState } from "../../entities/gamestates/GameState.js";

export interface IGameCondition {
  checkAndUpdate(currentGameState: GameState): void;
}
