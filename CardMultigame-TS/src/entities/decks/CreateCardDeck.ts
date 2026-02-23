import { Card } from "../cards/Card.js";
import { CreateCards } from "../cards/CreateCards.js";
import { ICardSelector } from "../../technical/rangens/ICardSelector.js";
import { RandomCardSelector } from "../../technical/rangens/RandomCardSelector.js";
import { CardDeck } from "./CardDeck.js";

export class CreateCardDeck {
  private selectedCardSelector: ICardSelector = new RandomCardSelector();

  fromGivenCards(cardsInDeck: string): CardDeck {
    const cards = new CreateCards().createCollection(cardsInDeck);
    return new CardDeck(this.selectedCardSelector, cards);
  }

  simple9ToAWith4Colours(): CardDeck {
    const ranks = ["9", "10", "J", "Q", "K", "A"];
    const colours = ["S", "H", "D", "C"];

    const cards: Card[] = [];
    for (const rank of ranks) {
      for (const colour of colours) {
        const cardPrototype = rank + colour;
        const card = new CreateCards().createSingle(cardPrototype);
        cards.push(card);
      }
    }
    return new CardDeck(this.selectedCardSelector, cards);
  }

  simple2ToAWith4Colours(): CardDeck {
    const ranks = [
      "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A",
    ];
    const colours = ["S", "H", "D", "C"];

    const cards: Card[] = [];
    for (const rank of ranks) {
      for (const colour of colours) {
        const cardPrototype = rank + colour;
        const card = new CreateCards().createSingle(cardPrototype);
        cards.push(card);
      }
    }
    return new CardDeck(this.selectedCardSelector, cards);
  }

  empty(): CardDeck {
    return new CardDeck(this.selectedCardSelector, []);
  }

  setCardSelector(selector: ICardSelector): void {
    this.selectedCardSelector = selector;
  }
}
