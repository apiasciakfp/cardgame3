import { IGameAction } from "./IGameAction.js";
import { DrawSingleCardAction } from "./DrawSingleCardAction.js";
import { AddQueenOfHeartsToDeck } from "./AddQueenOfHeartsToDeck.js";
import { Add10COrDrawACard } from "./Add10COrDrawACard.js";

export class CreateGameActions {
  havingOrders(actionsToPerform: string): IGameAction[] {
    const tokens = actionsToPerform.split(/\s+/);

    const actions: IGameAction[] = [];
    for (const token of tokens) {
      const sanitized = token.replace(",", "");

      if (sanitized === "drawSingleCard")
        actions.push(new DrawSingleCardAction());
      if (sanitized === "addQH") actions.push(new AddQueenOfHeartsToDeck());
      if (sanitized === "add10cOrDraw") actions.push(new Add10COrDrawACard());
    }

    return actions;
  }
}
