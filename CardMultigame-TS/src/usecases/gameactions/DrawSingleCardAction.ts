import { GameState } from "../../entities/gamestates/GameState.js";
import { PlayedGameRules } from "../../gamemanagers/selectedrules/PlayedGameRules.js";
import * as QueryGameState from "../influencestate/QueryGameState.js";
import { IGameAction } from "./IGameAction.js";

export class DrawSingleCardAction implements IGameAction {
  changeGameState(
    currentGameState: GameState,
    gameRules: PlayedGameRules | null,
    orderParams: string | null
  ): void {
    QueryGameState.extractCardDeck(currentGameState).drawRandomCard();

    if (QueryGameState.amountOfCardsLeft(currentGameState) === 0)
      currentGameState.set("Guess", true);
  }

  shouldReactTo(item: string): boolean {
    throw new Error("Not implemented");
  }
}
