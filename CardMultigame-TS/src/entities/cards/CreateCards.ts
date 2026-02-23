import { Card } from "./Card.js";

export class CreateCards {
  createCollection(cardStrings: string): Card[] {
    const cardPrototypePattern = /((\b\w{2,3}\b)+)/g;
    const cards: Card[] = [];

    let match: RegExpExecArray | null;
    while ((match = cardPrototypePattern.exec(cardStrings)) !== null) {
      const prototype = match[0];
      if (this.isValidCardPrototype(prototype)) {
        cards.push(this.createSingle(prototype));
      }
    }
    return cards;
  }

  createSingle(prototype: string): Card {
    if (!this.isValidCardPrototype(prototype)) {
      return this.damagedCard();
    }
    const rank = this.extractRank(prototype);
    const colour = this.extractColour(prototype);
    return new Card(rank, colour);
  }

  private extractColour(prototype: string): string {
    const colourSign = prototype.substring(prototype.length - 1);
    if (colourSign.toUpperCase() === "S") return "S";
    if (colourSign.toUpperCase() === "H") return "H";
    if (colourSign.toUpperCase() === "D") return "D";
    if (colourSign.toUpperCase() === "C") return "C";
    throw new Error(
      "Colour extraction failed. Instead of SHDC we got: " + colourSign
    );
  }

  private extractRank(prototype: string): string {
    return prototype.substring(0, prototype.length - 1);
  }

  private damagedCard(): Card {
    return new Card("Damaged", "Damaged");
  }

  private isValidCardPrototype(prototype: string): boolean {
    const exactCardPrototypePattern =
      /\b(10[shdcSHDC]|[2-9jqkaJQKA][shdcSHDC])\b/;
    return exactCardPrototypePattern.test(prototype);
  }
}
