import { GameState } from "../../entities/gamestates/GameState.js";
import { PlayedGameRules } from "../../gamemanagers/selectedrules/PlayedGameRules.js";

export interface IGameAction {
  shouldReactTo(item1: string): boolean;
  changeGameState(
    currentGameState: GameState,
    gameRules: PlayedGameRules | null,
    orderParams: string | null
  ): void;
}
