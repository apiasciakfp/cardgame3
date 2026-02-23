import { describe, it, expect } from "vitest";
import { CreateGameManager } from "../src/gamemanagers/CreateGameManager.js";
import * as QueryGameState from "../src/usecases/influencestate/QueryGameState.js";

describe("TestGuessACard", () => {
  it("directCardGuessingWorks_forThreeCardsDeck_failure", () => {
    // Given primitives
    const cards = ["JH", "QH", "KH"];
    const cardOutsideDeck = "2C";
    const secondSeparator = ",";
    const cardsInDeck = cards.join(secondSeparator);

    // Given
    const orders =
      "Play GuessACard; SetDeck " +
      cardsInDeck +
      "; SetMaxTurns 3; " +
      "Guess " +
      cardOutsideDeck +
      "; Guess " +
      cardOutsideDeck +
      "; Guess " +
      cardOutsideDeck;

    const gm = new CreateGameManager().defaultsWithOrders(orders);

    // When
    gm.executeOrders(orders);
    const resultReceived = gm.currentState();

    // Then
    expect(QueryGameState.gameUndergoing(resultReceived) === "Defeat").toBe(
      true
    );
    expect(
      QueryGameState.maximumTurns(resultReceived) ===
        QueryGameState.currentTurn(resultReceived)
    ).toBe(true);
    expect(QueryGameState.amountOfCardsLeft(resultReceived) === 0).toBe(true);
  });

  it("directCardGuessingWorks_forThreeCardsDeck_failure_diffSeparators", () => {
    // Given primitives
    const cards = ["JH", "QH", "KH"];
    const cardOutsideDeck = "2C";
    const secondSeparator = ";";
    const cardsInDeck = cards.join(secondSeparator);

    // Given
    const orders =
      "Play GuessACard, SetDeck " +
      cardsInDeck +
      ", SetMaxTurns 3, " +
      "Guess " +
      cardOutsideDeck +
      ", Guess " +
      cardOutsideDeck +
      ", Guess " +
      cardOutsideDeck;

    const gm = new CreateGameManager().defaultsWithOrders(orders);

    // When
    gm.executeOrders(orders);
    const resultReceived = gm.currentState();

    // Then
    expect(QueryGameState.gameUndergoing(resultReceived) === "Defeat").toBe(
      true
    );
    expect(
      QueryGameState.maximumTurns(resultReceived) ===
        QueryGameState.currentTurn(resultReceived)
    ).toBe(true);
    expect(QueryGameState.amountOfCardsLeft(resultReceived) === 0).toBe(true);
  });

  it("directCardGuessingWorks_forThreeCardsDeck_victory", () => {
    // Given primitives
    const cards = ["JH", "QH", "KH"];
    const cardInsideDeck = "JH";
    const secondSeparator = ",";
    const cardsInDeck = cards.join(secondSeparator);

    // Given
    const orders =
      "Play GuessACard; SetDeck " +
      cardsInDeck +
      "; SetMaxTurns 3; " +
      "Guess " +
      cardInsideDeck +
      "; Guess " +
      cardInsideDeck +
      "; Guess " +
      cardInsideDeck;

    const gm = new CreateGameManager().defaultsWithOrders(orders);

    // When
    gm.executeOrders(orders);
    const resultReceived = gm.currentState();

    // Then
    expect(QueryGameState.gameUndergoing(resultReceived) === "Victory").toBe(
      true
    );
  });

  it("cardRedBlackGuessingWorks_forThreeCardsOneColourDeck_missMissVictory", () => {
    // Given primitives
    const cards = ["JH", "QH", "KH"];
    const cardOutsideDeck = "2C";
    const cardInsideDeck = "2D";
    const secondSeparator = ",";
    const cardsInDeck = cards.join(secondSeparator);

    // Given
    const orders =
      "Play GuessACard; SetDeck " +
      cardsInDeck +
      "; GameVariant RedBlack; " +
      "Guess " +
      cardOutsideDeck +
      "; Guess " +
      cardOutsideDeck +
      "; Guess " +
      cardInsideDeck;

    const gm = new CreateGameManager().defaultsWithOrders(orders);

    // When
    gm.executeOrders(orders);
    const resultReceived = gm.currentState();

    // Then
    expect(QueryGameState.gameUndergoing(resultReceived) === "Victory").toBe(
      true
    );
  });
});
