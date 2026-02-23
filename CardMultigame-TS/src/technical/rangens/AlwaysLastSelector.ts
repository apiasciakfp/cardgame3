import { Card } from "../../entities/cards/Card.js";
import { ICardSelector } from "./ICardSelector.js";

export class AlwaysLastSelector implements ICardSelector {
  drawCard(cards: Card[]): Card {
    return cards[cards.length - 1];
  }
}
