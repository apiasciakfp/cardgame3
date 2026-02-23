import { Card } from "../../entities/cards/Card.js";

export interface ICardSelector {
  drawCard(cards: Card[]): Card;
}
