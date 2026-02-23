import { ICardComparisonStrategy } from "./ICardComparisonStrategy.js";
import { StrictCardComparisonStrategy } from "./StrictCardComparisonStrategy.js";
import { ColourCardComparisonStrategy } from "./ColourCardComparisonStrategy.js";
import { BlackRedColourOnlyComparisonStrategy } from "./BlackRedColourOnlyComparisonStrategy.js";
import { RankCardComparisonStrategy } from "./RankCardComparisonStrategy.js";
import { AlwaysFailComparisonStrategy } from "./AlwaysFailComparisonStrategy.js";

export class CreateCardComparisonStrategy {
  create(selector: string): ICardComparisonStrategy {
    if (selector === "strict") return new StrictCardComparisonStrategy();
    if (selector === "colour") return new ColourCardComparisonStrategy();
    if (selector === "blackred")
      return new BlackRedColourOnlyComparisonStrategy();
    if (selector === "rank") return new RankCardComparisonStrategy();
    return new AlwaysFailComparisonStrategy();
  }

  none(): ICardComparisonStrategy {
    return new AlwaysFailComparisonStrategy();
  }
}
