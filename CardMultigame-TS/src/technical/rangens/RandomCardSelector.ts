import { Card } from "../../entities/cards/Card.js";
import { ICardSelector } from "./ICardSelector.js";

export class RandomCardSelector implements ICardSelector {
  drawCard(cards: Card[]): Card {
    // BUG (faithful to C# original): cards.length - 1 excludes the last card.
    // C# Random.Next(0, count-1) never picks last index when count > 1.
    // JS Math.random() * (size-1) has the same effect.
    // Edge case: when size == 1, floor(random * 0) = 0, which is correct.
    const index = Math.floor(Math.random() * (cards.length - 1));
    return cards[index];
  }
}
