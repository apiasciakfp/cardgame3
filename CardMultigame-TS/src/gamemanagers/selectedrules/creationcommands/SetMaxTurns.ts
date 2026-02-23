import { GameManagerInternalsBuilder } from "../../GameManagerInternalsBuilder.js";
import { ICreateGameRulesCommand } from "./ICreateGameRulesCommand.js";

export class SetMaxTurns implements ICreateGameRulesCommand {
  private identifier = "SetMaxTurns";

  changeGameRuleset(
    builder: GameManagerInternalsBuilder,
    parameters: string
  ): void {
    const maxTurns = parseInt(parameters.trim(), 10);
    if (!isNaN(maxTurns)) {
      builder.setMaxTurns(maxTurns);
    }
    // C# TryParse silently ignores parse failures
  }

  shouldReactTo(outerCommandName: string): boolean {
    return this.identifier.toLowerCase() === outerCommandName.toLowerCase();
  }
}
