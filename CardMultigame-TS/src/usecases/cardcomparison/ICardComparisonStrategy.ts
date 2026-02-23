import { Card } from "../../entities/cards/Card.js";

export interface ICardComparisonStrategy {
  areTheSame(card1: Card, card2: Card): boolean;
}
