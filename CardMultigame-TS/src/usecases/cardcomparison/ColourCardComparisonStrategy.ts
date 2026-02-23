import { Card } from "../../entities/cards/Card.js";
import { ICardComparisonStrategy } from "./ICardComparisonStrategy.js";

export class ColourCardComparisonStrategy implements ICardComparisonStrategy {
  areTheSame(card1: Card, card2: Card): boolean {
    return card1.colour === card2.colour;
  }
}
