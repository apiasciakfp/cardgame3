import { GameManagerInternalsBuilder } from "../GameManagerInternalsBuilder.js";
import { ICreateGameRulesCommand } from "./creationcommands/ICreateGameRulesCommand.js";
import { SelectGame } from "./creationcommands/SelectGame.js";
import { SetDeck } from "./creationcommands/SetDeck.js";
import { SetMaxTurns } from "./creationcommands/SetMaxTurns.js";
import { GameVariant } from "./creationcommands/GameVariant.js";
import { ParsedOrder } from "../../technical/parsers/ParsedOrder.js";

export class CreateGameStructure {
  private commands: ICreateGameRulesCommand[];

  constructor() {
    this.commands = this.registerAvailableCreationCommands();
  }

  buildRulesAndInitialState(
    orders: ParsedOrder[]
  ): GameManagerInternalsBuilder {
    const builder = new GameManagerInternalsBuilder();
    for (const order of orders) {
      for (const orderUser of this.commands) {
        if (orderUser.shouldReactTo(order.command)) {
          orderUser.changeGameRuleset(builder, order.params);
        }
      }
    }

    return builder;
  }

  private registerAvailableCreationCommands(): ICreateGameRulesCommand[] {
    return [
      new SelectGame(),
      new SetDeck(),
      new SetMaxTurns(),
      new GameVariant(),
    ];
  }
}
