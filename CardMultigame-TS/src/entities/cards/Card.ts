export class Card {
  private readonly _rank: string;
  private readonly _colour: string;

  constructor(rank: string, colour: string) {
    this._rank = rank;
    this._colour = colour;
  }

  get rank(): string {
    return this._rank;
  }

  get colour(): string {
    return this._colour;
  }

  toString(): string {
    return `r: ${this._rank} c: ${this._colour}`;
  }
}
