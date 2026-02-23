import { CreateCardDeck } from "../../../entities/decks/CreateCardDeck.js";
import { GameManagerInternalsBuilder } from "../../GameManagerInternalsBuilder.js";
import { ICreateGameRulesCommand } from "./ICreateGameRulesCommand.js";

export class SetDeck implements ICreateGameRulesCommand {
  private identifier = "SetDeck";

  changeGameRuleset(
    builder: GameManagerInternalsBuilder,
    parameters: string
  ): void {
    const deck = new CreateCardDeck().fromGivenCards(parameters);
    builder.setDeck(deck);
  }

  shouldReactTo(outerCommandName: string): boolean {
    return this.identifier.toLowerCase() === outerCommandName.toLowerCase();
  }
}
