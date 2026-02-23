import { CreateCards } from "../../entities/cards/CreateCards.js";
import { GameState } from "../../entities/gamestates/GameState.js";
import { PlayedGameRules } from "../../gamemanagers/selectedrules/PlayedGameRules.js";
import * as QueryGameState from "../influencestate/QueryGameState.js";
import * as ModifyGameState from "../influencestate/ModifyGameState.js";
import { IGameAction } from "./IGameAction.js";

export class GuessCardAction implements IGameAction {
  private identifier = "Guess";

  changeGameState(
    currentGameState: GameState,
    rules: PlayedGameRules | null,
    orderParams: string | null
  ): void {
    const candidate = new CreateCards().createSingle(orderParams!);

    const deck = QueryGameState.extractCardDeck(currentGameState);
    const actuallyDrawnCard = deck.drawRandomCard();

    const comparator = rules!.cardComparator();

    const areTheSame = comparator.areTheSame(candidate, actuallyDrawnCard);

    if (areTheSame) currentGameState.set(this.identifier, true);
    else currentGameState.set(this.identifier, false);

    ModifyGameState.addTurn(currentGameState);
  }

  shouldReactTo(orderName: string): boolean {
    return this.identifier.toLowerCase() === orderName.toLowerCase();
  }
}
