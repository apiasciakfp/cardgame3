import { Card } from "../../entities/cards/Card.js";
import { GameState } from "../../entities/gamestates/GameState.js";
import { PlayedGameRules } from "../../gamemanagers/selectedrules/PlayedGameRules.js";
import * as QueryGameState from "../influencestate/QueryGameState.js";
import { IGameAction } from "./IGameAction.js";

export class Add10COrDrawACard implements IGameAction {
  changeGameState(
    currentGameState: GameState,
    gameRules: PlayedGameRules | null,
    orderParams: string | null
  ): void {
    const deck = QueryGameState.extractCardDeck(currentGameState);

    if (QueryGameState.amountOfCardsLeft(currentGameState) % 2 === 0) {
      deck.addASingleCard(new Card("10", "C"));
    } else {
      deck.drawRandomCard();
    }
  }

  shouldReactTo(item: string): boolean {
    throw new Error("Not implemented");
  }
}
