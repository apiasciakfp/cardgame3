import { Card } from "../../entities/cards/Card.js";
import { GameState } from "../../entities/gamestates/GameState.js";
import { PlayedGameRules } from "../../gamemanagers/selectedrules/PlayedGameRules.js";
import * as QueryGameState from "../influencestate/QueryGameState.js";
import { IGameAction } from "./IGameAction.js";

export class AddQueenOfHeartsToDeck implements IGameAction {
  changeGameState(
    currentGameState: GameState,
    gameRules: PlayedGameRules | null,
    orderParams: string | null
  ): void {
    const deck = QueryGameState.extractCardDeck(currentGameState);
    deck.addASingleCard(new Card("Q", "H"));
  }

  shouldReactTo(item: string): boolean {
    throw new Error("Not implemented");
  }
}
