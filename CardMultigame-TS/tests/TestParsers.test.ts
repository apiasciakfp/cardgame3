import { describe, it, expect } from "vitest";
import { parsedOrder } from "../src/technical/parsers/ParsedOrder.js";
import { SelectedParser } from "../src/technical/parsers/SelectedParser.js";

describe("TestParsers", () => {
  it("parserProperlySelected_semicolonSeparator", () => {
    // Expecting
    const ordersExpected = [
      parsedOrder("Play", "GuessACard"),
      parsedOrder("SetDeck", "JH, QH, KH"),
      parsedOrder("StartGame", ""),
      parsedOrder("Guess", "JH"),
      parsedOrder("Guess", "QH"),
    ];

    // Given
    const ordersString =
      "Play GuessACard; SetDeck JH, QH, KH; StartGame; Guess JH; Guess QH";

    // When
    const ordersReceived = new SelectedParser().properlyParse(ordersString);

    // Then
    for (let i = 0; i < ordersExpected.length; i++) {
      expect(ordersReceived[i]).toEqual(ordersExpected[i]);
    }
  });

  it("parserProperlySelected_commaSeparator", () => {
    // Expecting
    const ordersExpected = [
      parsedOrder("Play", "GuessACard"),
      parsedOrder("SetDeck", "JH; QH; KH"),
      parsedOrder("StartGame", ""),
      parsedOrder("Guess", "JH"),
      parsedOrder("Guess", "QH"),
    ];

    // Given
    const ordersString =
      "Play GuessACard, SetDeck JH; QH; KH, StartGame, Guess JH, Guess QH";

    // When
    const ordersReceived = new SelectedParser().properlyParse(ordersString);

    // Then
    for (let i = 0; i < ordersExpected.length; i++) {
      expect(ordersReceived[i]).toEqual(ordersExpected[i]);
    }
  });
});
