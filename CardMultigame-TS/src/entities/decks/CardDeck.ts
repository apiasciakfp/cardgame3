import { Card } from "../cards/Card.js";
import { ICardSelector } from "../../technical/rangens/ICardSelector.js";
import { RandomCardSelector } from "../../technical/rangens/RandomCardSelector.js";

export class CardDeck {
  private _selector: ICardSelector = new RandomCardSelector();
  private _cards: Card[] = [];

  constructor(selector: ICardSelector, cards: Card[]) {
    this._selector = selector;
    this._cards = cards;
  }

  allCards(): Card[] {
    return this._cards;
  }

  cardsLeft(): number {
    return this._cards.length;
  }

  drawRandomCard(): Card {
    const drawn = this._selector.drawCard(this._cards);
    const index = this._cards.indexOf(drawn);
    this._cards.splice(index, 1);
    return drawn;
  }

  drawLastAddedCard(): Card {
    const drawn = this._cards[this._cards.length - 1];
    this._cards.splice(this._cards.length - 1, 1);
    return drawn;
  }

  addASingleCard(card: Card): void {
    this._cards.push(card);
  }

  toString(): string {
    const cardFaces = this._cards
      .map((card) => card.toString())
      .reduce((acc, card) => acc + "||" + card, "");
    return "Deck: " + cardFaces;
  }
}
