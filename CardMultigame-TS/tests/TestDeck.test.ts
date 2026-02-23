import { describe, it, expect } from "vitest";
import { Card } from "../src/entities/cards/Card.js";
import { CreateCards } from "../src/entities/cards/CreateCards.js";
import { CardDeck } from "../src/entities/decks/CardDeck.js";
import { CreateCardDeck } from "../src/entities/decks/CreateCardDeck.js";
import { StrictCardComparisonStrategy } from "../src/usecases/cardcomparison/StrictCardComparisonStrategy.js";

describe("TestDeck", () => {
  it("drawCardFromDeck_randomly_5CardsUntil0Left", () => {
    // Given
    const cardSigils = ["9H", "10H", "JH", "QH", "KH"];
    const separator = ",";
    const cardsInDeck = cardSigils.join(separator);

    const cards = new CreateCards().createCollection(cardsInDeck);
    const deck = new CreateCardDeck().fromGivenCards(cardsInDeck);

    // Expecting
    const lengthInDeck = 0;
    const lengthOfDrawnCards = cards.length;

    // When
    const drawnCards: Card[] = [];
    for (let i = 0; i < cardSigils.length; i++) {
      drawnCards.push(deck.drawRandomCard());
    }

    // Then
    const cardsRemaining = deck.allCards();

    expect(cardsRemaining.length === lengthInDeck).toBe(true);
    expect(drawnCards.length === lengthOfDrawnCards).toBe(true);
  });

  it("createDeck_withStandardCards9ToAWith4Colours", () => {
    // Given
    // Expecting
    const cardCountExpected = 24;

    // When
    const deck = new CreateCardDeck().simple9ToAWith4Colours();

    // Then
    const cardsReceived = deck.allCards();

    expect(cardsReceived.length === cardCountExpected).toBe(true);
  });

  it("createDeck_with3SetCards_inCommaFormat", () => {
    // Given
    const cards = ["JH", "QH", "KH"];
    const separator = ",";
    const cardsInDeck = cards.join(separator);

    // Expecting
    const cardsExpected = new CreateCards().createCollection(cardsInDeck);

    // When
    const deck = new CreateCardDeck().fromGivenCards(cardsInDeck);

    // Then
    const cardsReceived = deck.allCards();

    expect(cardsExpected.length === cardsReceived.length).toBe(true);

    for (let i = 0; i < cardsExpected.length; i++) {
      expect(
        new StrictCardComparisonStrategy().areTheSame(
          cardsExpected[i],
          cardsReceived[i]
        )
      ).toBe(true);
    }
  });
});
