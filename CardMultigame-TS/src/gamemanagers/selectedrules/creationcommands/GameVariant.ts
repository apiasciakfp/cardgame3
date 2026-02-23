import { BlackRedColourOnlyComparisonStrategy } from "../../../usecases/cardcomparison/BlackRedColourOnlyComparisonStrategy.js";
import { GameManagerInternalsBuilder } from "../../GameManagerInternalsBuilder.js";
import { ICreateGameRulesCommand } from "./ICreateGameRulesCommand.js";

export class GameVariant implements ICreateGameRulesCommand {
  private identifier = "GameVariant";

  changeGameRuleset(
    builder: GameManagerInternalsBuilder,
    parameters: string
  ): void {
    builder.setCardComparisonStrategy(
      new BlackRedColourOnlyComparisonStrategy()
    );
  }

  shouldReactTo(outerCommandName: string): boolean {
    return this.identifier.toLowerCase() === outerCommandName.toLowerCase();
  }
}
