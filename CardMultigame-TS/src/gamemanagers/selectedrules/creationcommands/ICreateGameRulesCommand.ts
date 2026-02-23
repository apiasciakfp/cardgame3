import { GameManagerInternalsBuilder } from "../../GameManagerInternalsBuilder.js";

export interface ICreateGameRulesCommand {
  shouldReactTo(outerCommandName: string): boolean;
  changeGameRuleset(
    builder: GameManagerInternalsBuilder,
    parameters: string
  ): void;
}
