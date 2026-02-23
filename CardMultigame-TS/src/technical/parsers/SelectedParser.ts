import { IParseStrategy } from "./parsestrategies/IParseStrategy.js";
import { CommaParseStrategy } from "./parsestrategies/CommaParseStrategy.js";
import { SemicolonParseStrategy } from "./parsestrategies/SemicolonParseStrategy.js";
import { DashParseStrategy } from "./parsestrategies/DashParseStrategy.js";
import { ParsedOrder } from "./ParsedOrder.js";
import { PerformParsing } from "./PerformParsing.js";

export class SelectedParser {
  private readonly parseStrategies: IParseStrategy[];

  constructor() {
    this.parseStrategies = this.registerPossibleStrategies();
  }

  properlyParse(orderString: string): ParsedOrder[] {
    const selectedStrategy = this.selectAppropriateStrategy(orderString);

    if (selectedStrategy === null) {
      throw new Error(
        "Order string is wrong or appropriate parsing Strategy is not registered"
      );
    }

    return new PerformParsing(selectedStrategy).executeOn(orderString);
  }

  private selectAppropriateStrategy(
    orderString: string
  ): IParseStrategy | null {
    let lastPosition = Number.MAX_SAFE_INTEGER;
    let selectedStrategy: IParseStrategy | null = null;

    for (const strategy of this.parseStrategies) {
      const potential = strategy.separator();
      const currentPosition = orderString.indexOf(potential);

      // BUG (faithful to C# original): > 0 rejects separator at position 0.
      // Should be >= 0 to accept separators at the start of the string.
      if (currentPosition > 0 && currentPosition < lastPosition) {
        selectedStrategy = strategy;
        lastPosition = currentPosition;
      }
    }

    return selectedStrategy;
  }

  private registerPossibleStrategies(): IParseStrategy[] {
    return [
      new CommaParseStrategy(),
      new SemicolonParseStrategy(),
      new DashParseStrategy(),
    ];
  }
}
