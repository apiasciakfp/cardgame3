import { Card } from "../../entities/cards/Card.js";
import { ICardSelector } from "./ICardSelector.js";

export class AlwaysFirstSelector implements ICardSelector {
  drawCard(cards: Card[]): Card {
    return cards[0];
  }
}
