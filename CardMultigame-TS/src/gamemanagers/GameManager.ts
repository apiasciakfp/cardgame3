import { GameState } from "../entities/gamestates/GameState.js";
import { PlayedGameRules } from "./selectedrules/PlayedGameRules.js";
import { SelectedParser } from "../technical/parsers/SelectedParser.js";
import * as QueryGameState from "../usecases/influencestate/QueryGameState.js";

export class GameManager {
  private currentGameState: GameState;
  private gameRules: PlayedGameRules;

  constructor(initialState: GameState, rules: PlayedGameRules) {
    this.currentGameState = initialState;
    this.gameRules = rules;
  }

  executeOrders(orderString: string): void {
    const orders = new SelectedParser().properlyParse(orderString);

    for (const order of orders) {
      if (QueryGameState.isGameFinished(this.currentGameState)) return;

      for (const gameAction of this.gameRules.gameActions()) {
        if (gameAction.shouldReactTo(order.command)) {
          gameAction.changeGameState(
            this.currentGameState,
            this.gameRules,
            order.params
          );

          // CRITICAL: victory checked BEFORE game stop (load-bearing order)
          this.gameRules.checkVictoryConditions(this.currentGameState);
          this.gameRules.checkGameStopConditions(this.currentGameState);
        }
      }
    }
  }

  currentState(): GameState {
    return this.currentGameState;
  }
}
