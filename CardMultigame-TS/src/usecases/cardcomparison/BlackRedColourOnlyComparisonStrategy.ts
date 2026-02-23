import { Card } from "../../entities/cards/Card.js";
import { ICardComparisonStrategy } from "./ICardComparisonStrategy.js";

export class BlackRedColourOnlyComparisonStrategy
  implements ICardComparisonStrategy
{
  areTheSame(card1: Card, card2: Card): boolean {
    const colourMap: Record<string, string> = {
      H: "red",
      D: "red",
      C: "black",
      S: "black",
    };

    const card1Colour = colourMap[card1.colour];
    const card2Colour = colourMap[card2.colour];

    return card1Colour === card2Colour;
  }
}
