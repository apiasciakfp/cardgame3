import { describe, it, expect } from "vitest";
import { Card } from "../src/entities/cards/Card.js";
import { CreateCards } from "../src/entities/cards/CreateCards.js";
import { CardDeck } from "../src/entities/decks/CardDeck.js";
import { CreateCardDeck } from "../src/entities/decks/CreateCardDeck.js";
import { AlwaysFirstSelector } from "../src/technical/rangens/AlwaysFirstSelector.js";
import { AlwaysLastSelector } from "../src/technical/rangens/AlwaysLastSelector.js";
import { parsedOrder } from "../src/technical/parsers/ParsedOrder.js";
import { SelectedParser } from "../src/technical/parsers/SelectedParser.js";
import { ICardComparisonStrategy } from "../src/usecases/cardcomparison/ICardComparisonStrategy.js";
import { StrictCardComparisonStrategy } from "../src/usecases/cardcomparison/StrictCardComparisonStrategy.js";
import { ColourCardComparisonStrategy } from "../src/usecases/cardcomparison/ColourCardComparisonStrategy.js";
import { RankCardComparisonStrategy } from "../src/usecases/cardcomparison/RankCardComparisonStrategy.js";
import { BlackRedColourOnlyComparisonStrategy } from "../src/usecases/cardcomparison/BlackRedColourOnlyComparisonStrategy.js";
import { CreateCardComparisonStrategy } from "../src/usecases/cardcomparison/CreateCardComparisonStrategy.js";
import { GuessACardGame } from "../src/entities/games/GuessACardGame.js";

describe("Batch100", () => {
  it("T_101: strategyBasics", () => {
    const card1 = new Card("J", "H");
    const identicalCard = new Card("J", "H");
    const differentCard = new Card("K", "H");

    const areTheSameWithIdentical = new StrictCardComparisonStrategy().areTheSame(card1, identicalCard);
    const areTheSameWithDifferent = new StrictCardComparisonStrategy().areTheSame(card1, differentCard);

    expect(areTheSameWithIdentical).toBe(true);
    expect(areTheSameWithDifferent).toBe(false);
  });

  it("T_102: implementYourOwnStrategy", () => {
    const card1 = new Card("J", "H");
    const identicalCard = new Card("2", "H");
    const differentCard = new Card("J", "D");

    const areTheSameWithIdentical = new ColourCardComparisonStrategy().areTheSame(card1, identicalCard);
    const areTheSameWithDifferent = new ColourCardComparisonStrategy().areTheSame(card1, differentCard);

    expect(areTheSameWithIdentical).toBe(true);
    expect(areTheSameWithDifferent).toBe(false);
  });

  it("T_103: implementTheBlackRedStrategy", () => {
    const reference = new Card("2", "H");
    const identical1 = new Card("2", "H");
    const identical2 = new Card("7", "D");
    const different1 = new Card("2", "S");
    const different2 = new Card("Q", "C");

    expect(new BlackRedColourOnlyComparisonStrategy().areTheSame(reference, identical1)).toBe(true);
    expect(new BlackRedColourOnlyComparisonStrategy().areTheSame(reference, identical2)).toBe(true);
    expect(new BlackRedColourOnlyComparisonStrategy().areTheSame(reference, different1)).toBe(false);
    expect(new BlackRedColourOnlyComparisonStrategy().areTheSame(reference, different2)).toBe(false);
  });

  it("T_104: powerOfPolymorphism", () => {
    const card1 = new Card("J", "H");
    const card2 = new Card("A", "H");

    let strategy: ICardComparisonStrategy;

    strategy = new StrictCardComparisonStrategy();
    expect(strategy.areTheSame(card1, card2)).toBe(false);

    strategy = new ColourCardComparisonStrategy();
    expect(strategy.areTheSame(card1, card2)).toBe(true);

    strategy = new RankCardComparisonStrategy();
    expect(strategy.areTheSame(card1, card2)).toBe(false);

    strategy = new BlackRedColourOnlyComparisonStrategy();
    expect(strategy.areTheSame(card1, card2)).toBe(true);
  });

  it("T_105: factoryMethod_oneStrategyOnly", () => {
    const card1 = new Card("J", "H");
    const card2 = new Card("A", "H");

    const strategy = new CreateCardComparisonStrategy().create("colour");
    const areTheSame = strategy.areTheSame(card1, card2);

    expect(areTheSame).toBe(true);
  });

  it("T_106: factoryMethod_allStrategies", () => {
    const card1 = new Card("J", "H");
    const card2 = new Card("A", "H");

    let strategy: ICardComparisonStrategy;

    strategy = new CreateCardComparisonStrategy().create("strict");
    expect(strategy.areTheSame(card1, card2)).toBe(false);

    strategy = new CreateCardComparisonStrategy().create("colour");
    expect(strategy.areTheSame(card1, card2)).toBe(true);

    strategy = new CreateCardComparisonStrategy().create("rank");
    expect(strategy.areTheSame(card1, card2)).toBe(false);

    strategy = new CreateCardComparisonStrategy().create("blackred");
    expect(strategy.areTheSame(card1, card2)).toBe(true);
  });

  it("T_107: nullObjectWeAllLove", () => {
    const card1 = new Card("J", "H");
    const card2 = new Card("A", "H");

    const strategies = [
      new CreateCardComparisonStrategy().create("THIS IS A TYPO!"),
      new CreateCardComparisonStrategy().create(""),
      new CreateCardComparisonStrategy().create("al/fdkafklfhflsdhflhffhfh"),
      new CreateCardComparisonStrategy().create("f;lff;kklfs;df"),
      new CreateCardComparisonStrategy().create("don't else-if those cases please..."),
    ];

    for (const strategy of strategies) {
      expect(strategy.areTheSame(card1, card2)).toBe(false);
    }
  });

  it("T_108: letsPrepareTheStrategyForTheFuture", () => {
    // Given - nothing
    // When
    const selectedStrategy = new GuessACardGame().cardComparisonStrategy();

    // Then
    expect(selectedStrategy instanceof StrictCardComparisonStrategy).toBe(true);
  });

  it("T_109: cardDeckNeedsDifferentCreationWays", () => {
    const cardsBetween2A = 13;
    const cardColours = 4;
    const totalCards = cardsBetween2A * cardColours;

    const lowCard = new Card("2", "C");
    const highCard = new Card("K", "H");

    const deck = new CreateCardDeck().simple2ToAWith4Colours();
    const allCards = deck.allCards();

    let foundSmall = false;
    let foundLarge = false;

    for (const card of allCards) {
      if (new StrictCardComparisonStrategy().areTheSame(card, lowCard)) foundSmall = true;
      if (new StrictCardComparisonStrategy().areTheSame(card, highCard)) foundLarge = true;
    }

    expect(foundSmall).toBe(true);
    expect(foundLarge).toBe(true);
  });

  it("T_110: parsers_ofCourseParsers", () => {
    // Case1: ';' as main delimiter, ',' as second.
    let ordersExpected = [
      parsedOrder("Play", "GuessACard"),
      parsedOrder("SetDeck", "JH, QH, KH"),
      parsedOrder("StartGame", ""),
      parsedOrder("Guess", "JH"),
      parsedOrder("Guess", "QH"),
    ];
    let ordersString =
      "Play GuessACard; SetDeck JH, QH, KH; StartGame; Guess JH; Guess QH";
    let ordersReceived = new SelectedParser().properlyParse(ordersString);
    for (let i = 0; i < ordersExpected.length; i++) {
      expect(ordersReceived[i]).toEqual(ordersExpected[i]);
    }

    // Case2: ',' as main delimiter, ';' as second.
    ordersExpected = [
      parsedOrder("Play", "GuessACard"),
      parsedOrder("SetDeck", "JH; QH; KH"),
      parsedOrder("StartGame", ""),
      parsedOrder("Guess", "JH"),
      parsedOrder("Guess", "QH"),
    ];
    ordersString =
      "Play GuessACard, SetDeck JH; QH; KH, StartGame, Guess JH, Guess QH";
    ordersReceived = new SelectedParser().properlyParse(ordersString);
    for (let i = 0; i < ordersExpected.length; i++) {
      expect(ordersReceived[i]).toEqual(ordersExpected[i]);
    }

    // Case3: '-' as main delimiter, ',' as second.
    ordersExpected = [
      parsedOrder("Play", "GuessACard"),
      parsedOrder("SetDeck", "JH, QH, KH"),
      parsedOrder("StartGame", ""),
      parsedOrder("Guess", "JH"),
      parsedOrder("Guess", "QH"),
    ];
    ordersString =
      "Play GuessACard - SetDeck JH, QH, KH - StartGame - Guess JH - Guess QH";
    ordersReceived = new SelectedParser().properlyParse(ordersString);
    for (let i = 0; i < ordersExpected.length; i++) {
      expect(ordersReceived[i]).toEqual(ordersExpected[i]);
    }
  });

  it("T_111: cardDeckCanHaveConfiguredRandomGenerator_first", () => {
    // Given, Expected
    const selector = new AlwaysFirstSelector();
    const expectedCards = new CreateCards().createCollection(
      "9H, 10H, 9C, 10C, AD"
    );

    const copiedList = [...expectedCards];
    const deck = new CardDeck(selector, copiedList);

    // When
    const actualCards: Card[] = [];
    for (let i = 0; i < 5; i++) {
      actualCards.push(deck.drawRandomCard());
    }

    // Then
    for (let i = 0; i < 5; i++) {
      expect(expectedCards[i].colour === actualCards[i].colour).toBe(true);
      expect(expectedCards[i].rank === actualCards[i].rank).toBe(true);
    }
  });

  it("T_112: cardDeckCanHaveConfiguredRandomGenerator_last", () => {
    // Given, Expected
    const selector = new AlwaysLastSelector();
    const expectedCards = new CreateCards().createCollection(
      "9H, 10H, 9C, 10C, AD"
    );

    const copiedList = [...expectedCards];
    const deck = new CardDeck(selector, copiedList);

    // When
    const actualCards: Card[] = [];
    for (let i = 0; i < 5; i++) {
      actualCards.push(deck.drawRandomCard());
    }

    // Then
    for (let i = 0; i < 5; i++) {
      expect(expectedCards[4 - i].colour === actualCards[i].colour).toBe(
        true
      );
      expect(expectedCards[4 - i].rank === actualCards[i].rank).toBe(true);
    }
  });

  it("T_113: cardDeckFactory_canReconfigureRandomGenerator", () => {
    // Given
    const inputCardSigils = "JS, QH, KD, AC";

    // Expected
    const expectedCards = new CreateCards().createCollection(inputCardSigils);

    // Given: look at this CLOSELY
    const creator = new CreateCardDeck();

    creator.setCardSelector(new AlwaysFirstSelector());
    const deckWithAlwaysFirst = creator.fromGivenCards(inputCardSigils);

    // When
    const actualFirstCards: Card[] = [];
    for (let i = 0; i < 4; i++) {
      actualFirstCards.push(deckWithAlwaysFirst.drawRandomCard());
    }

    // Then
    for (let i = 0; i < 4; i++) {
      expect(
        expectedCards[i].colour === actualFirstCards[i].colour
      ).toBe(true);
      expect(expectedCards[i].rank === actualFirstCards[i].rank).toBe(
        true
      );
    }

    // Given again
    creator.setCardSelector(new AlwaysLastSelector());
    const deckWithAlwaysLast = creator.fromGivenCards(inputCardSigils);

    // When
    const actualLastCards: Card[] = [];
    for (let i = 0; i < 4; i++) {
      actualLastCards.push(deckWithAlwaysLast.drawRandomCard());
    }

    // Then
    for (let i = 0; i < 4; i++) {
      expect(
        expectedCards[3 - i].colour === actualLastCards[i].colour
      ).toBe(true);
      expect(expectedCards[3 - i].rank === actualLastCards[i].rank).toBe(
        true
      );
    }
  });
});
