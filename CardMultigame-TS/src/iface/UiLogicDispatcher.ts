import { GameState } from "../entities/gamestates/GameState.js";
import { CreateGameManager } from "../gamemanagers/CreateGameManager.js";
import { GameManager } from "../gamemanagers/GameManager.js";

export class UiLogicDispatcher {
  private gameManager: GameManager;

  constructor() {
    this.gameManager = new CreateGameManager().empty();
  }

  doStuff(orders: string): void {
    this.gameManager.executeOrders(orders);
  }

  setupGame(orders: string): void {
    this.gameManager = new CreateGameManager().defaultsWithOrders(orders);
  }

  displayCurrentState(): string {
    const currentState: GameState = this.gameManager.currentState();
    const entries: string[] = [];
    for (const [key, value] of currentState) {
      entries.push(`${key}=${value}`);
    }
    return entries.join(";\n");
  }
}
