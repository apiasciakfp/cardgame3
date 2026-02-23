import { Card } from "../../entities/cards/Card.js";
import { ICardComparisonStrategy } from "./ICardComparisonStrategy.js";

export class AlwaysFailComparisonStrategy implements ICardComparisonStrategy {
  areTheSame(card1: Card, card2: Card): boolean {
    return false;
  }
}
