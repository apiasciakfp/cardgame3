import { describe, it, expect } from "vitest";
import { CreateCardDeck } from "../src/entities/decks/CreateCardDeck.js";
import { CreateGameState } from "../src/entities/gamestates/CreateGameState.js";
import { GameStateKeys } from "../src/entities/gamestates/GameStateKeys.js";
import { CreatePlayedGameRules } from "../src/gamemanagers/selectedrules/CreatePlayedGameRules.js";
import { AlwaysFailComparisonStrategy } from "../src/usecases/cardcomparison/AlwaysFailComparisonStrategy.js";
import { IGameAction } from "../src/usecases/gameactions/IGameAction.js";
import { DrawSingleCardAction } from "../src/usecases/gameactions/DrawSingleCardAction.js";
import { AddQueenOfHeartsToDeck } from "../src/usecases/gameactions/AddQueenOfHeartsToDeck.js";
import { Add10COrDrawACard } from "../src/usecases/gameactions/Add10COrDrawACard.js";
import { CreateGameActions } from "../src/usecases/gameactions/CreateGameActions.js";
import { GuessCardAction } from "../src/usecases/gameactions/GuessCardAction.js";
import { IGameCondition } from "../src/usecases/gameconditions/IGameCondition.js";
import { DidGuessACard } from "../src/usecases/gameconditions/DidGuessACard.js";
import { DidTurnsExpire } from "../src/usecases/gameconditions/DidTurnsExpire.js";
import * as QueryGameState from "../src/usecases/influencestate/QueryGameState.js";
import * as ModifyGameState from "../src/usecases/influencestate/ModifyGameState.js";
import { GuessACardGame } from "../src/entities/games/GuessACardGame.js";
import { GameManagerInternalsBuilder } from "../src/gamemanagers/GameManagerInternalsBuilder.js";
import { SelectGame } from "../src/gamemanagers/selectedrules/creationcommands/SelectGame.js";
import { GameVariant } from "../src/gamemanagers/selectedrules/creationcommands/GameVariant.js";
import { SetDeck } from "../src/gamemanagers/selectedrules/creationcommands/SetDeck.js";
import { ICreateGameRulesCommand } from "../src/gamemanagers/selectedrules/creationcommands/ICreateGameRulesCommand.js";
import { StrictCardComparisonStrategy } from "../src/usecases/cardcomparison/StrictCardComparisonStrategy.js";
import { BlackRedColourOnlyComparisonStrategy } from "../src/usecases/cardcomparison/BlackRedColourOnlyComparisonStrategy.js";

describe("Batch200", () => {
  it("T_201: gentleIntroductionToCommand", () => {
    // Tutorial
    const tutorialState = new CreateGameState().defaultsWithFullDeck();
    const tutorialDeck = QueryGameState.extractCardDeck(tutorialState);
    tutorialDeck.drawRandomCard();

    // Given
    const deck = new CreateCardDeck().fromGivenCards("2H, 3H, 4H");
    const gameState = new CreateGameState().defaultsPlusDeck(deck);

    // Expected
    expect(QueryGameState.amountOfCardsLeft(gameState) === 3).toBe(true);
    const amountOfCardsAfterDrawingOne =
      QueryGameState.amountOfCardsLeft(gameState) - 1;

    // When
    new DrawSingleCardAction().changeGameState(gameState, null, null);

    // Then
    expect(
      QueryGameState.amountOfCardsLeft(gameState) ===
        amountOfCardsAfterDrawingOne
    ).toBe(true);
  });

  it("T_202: addSome_QH_intoTheCardDeck", () => {
    // Given
    const deck = new CreateCardDeck().fromGivenCards("2H, 3H, 4H");
    const gameState = new CreateGameState().defaultsPlusDeck(deck);

    const actions: IGameAction[] = [
      new AddQueenOfHeartsToDeck(),
      new AddQueenOfHeartsToDeck(),
      new AddQueenOfHeartsToDeck(),
      new AddQueenOfHeartsToDeck(),
      new AddQueenOfHeartsToDeck(),
    ];

    // Expected
    expect(QueryGameState.amountOfCardsLeft(gameState) === 3).toBe(true);
    const amountOfCardsAfterDrawingOne =
      QueryGameState.amountOfCardsLeft(gameState) + actions.length;

    // When
    for (const action of actions) {
      action.changeGameState(gameState, null, null);
    }

    // Then
    expect(
      QueryGameState.amountOfCardsLeft(gameState) ===
        amountOfCardsAfterDrawingOne
    ).toBe(true);

    const retrievedDeck = QueryGameState.extractCardDeck(gameState);

    for (let i = 0; i < 5; i++) {
      const card = retrievedDeck.drawLastAddedCard();
      expect(card.rank === "Q").toBe(true);
      expect(card.colour === "H").toBe(true);
    }
  });

  it("T_203: chainSomeCommands", () => {
    // Given
    const deck = new CreateCardDeck().fromGivenCards("2H, 3H, 4H");
    const gameState = new CreateGameState().defaultsPlusDeck(deck);

    const actions: IGameAction[] = [
      new DrawSingleCardAction(),
      new DrawSingleCardAction(),
      new DrawSingleCardAction(), // now it should be empty
      new AddQueenOfHeartsToDeck(),
      new AddQueenOfHeartsToDeck(),
      new Add10COrDrawACard(), // should add +1 card, because even
      new Add10COrDrawACard(), // should draw a card, because odd
    ];

    // Expected
    expect(QueryGameState.amountOfCardsLeft(gameState) === 3).toBe(true);
    const amountOfCardsAfterDrawingOne = 2;

    // When
    for (const action of actions) {
      action.changeGameState(gameState, null, null);
    }

    // Then
    expect(
      QueryGameState.amountOfCardsLeft(gameState) ===
        amountOfCardsAfterDrawingOne
    ).toBe(true);
  });

  it("T_204: factorizeMe", () => {
    // Given
    const deck = new CreateCardDeck().fromGivenCards("2H, 3H, 4H");
    const gameState = new CreateGameState().defaultsPlusDeck(deck);

    const actionsToPerform =
      "drawSingleCard, drawSingleCard, drawSingleCard, addQH, addQH, " +
      "add10cOrDraw, add10cOrDraw";
    const actions = new CreateGameActions().havingOrders(actionsToPerform);

    // Expected
    expect(QueryGameState.amountOfCardsLeft(gameState) === 3).toBe(true);
    const amountOfCardsAfterDrawingOne = 2;

    // When
    for (const action of actions) {
      action.changeGameState(gameState, null, null);
    }

    // Then
    expect(
      QueryGameState.amountOfCardsLeft(gameState) ===
        amountOfCardsAfterDrawingOne
    ).toBe(true);
  });

  it("T_205: commandsCanCommunicateViaContext", () => {
    // Tutorial
    const tutorialState = new CreateGameState().defaultState();
    expect(tutorialState.get("SpecificKey") === undefined).toBe(true);
    tutorialState.set("SpecificKey", "Capybara");
    expect(
      (tutorialState.get("SpecificKey") as string) === "Capybara"
    ).toBe(true);

    // Given
    const deck = new CreateCardDeck().fromGivenCards("2H, 3H, 4H");
    const gameState = new CreateGameState().defaultsPlusDeck(deck);

    const actionsToPerform =
      "drawSingleCard, drawSingleCard, drawSingleCard";
    const actions = new CreateGameActions().havingOrders(actionsToPerform);

    // Expected
    expect(QueryGameState.amountOfCardsLeft(gameState) === 3).toBe(true);

    // When
    for (const action of actions) {
      action.changeGameState(gameState, null, null);
    }

    // Then
    expect((gameState.get("Guess") as boolean) === true).toBe(true);
  });

  it("T_206: queryGameState_cannotChangeAThing", () => {
    // Given
    const gameState = new CreateGameState().defaultState();
    gameState.set(GameStateKeys.IsGameWon, false);
    gameState.set(GameStateKeys.IsGameLost, false);

    // When
    // Then
    expect(QueryGameState.isGameWon(gameState) === false).toBe(true);
    expect(QueryGameState.isGameLost(gameState) === false).toBe(true);
  });

  it("T_207: modifyGameState_canChangeQuiteALot", () => {
    // Given
    const gameState = new CreateGameState().defaultState();
    gameState.set(GameStateKeys.IsGameWon, false);
    gameState.set(GameStateKeys.IsGameLost, false);

    // Given: making sure
    expect(QueryGameState.isGameWon(gameState) === false).toBe(true);
    expect(QueryGameState.isGameLost(gameState) === false).toBe(true);

    // When
    ModifyGameState.declareGameToBeWon(gameState);
    ModifyGameState.declareGameToBeLost(gameState);

    // Then
    expect(QueryGameState.isGameWon(gameState) === true).toBe(true);
    expect(QueryGameState.isGameLost(gameState) === true).toBe(true);
  });

  it("T_208: winConditionLossCondition", () => {
    // Given
    const gameState = new CreateGameState().defaultsWithFullDeck();

    const actionsToPerform = "drawSingleCard, drawSingleCard";
    const actions = new CreateGameActions().havingOrders(actionsToPerform);

    const conditions: IGameCondition[] = [
      new DidGuessACard(),
      new DidTurnsExpire(),
    ];

    // When
    do {
      for (const action of actions) {
        action.changeGameState(gameState, null, null);
      }

      for (const condition of conditions) {
        condition.checkAndUpdate(gameState);
      }
    } while (QueryGameState.isGameFinished(gameState) === false);

    // Then
    expect(QueryGameState.isGameLost(gameState) === true).toBe(true);
    expect(QueryGameState.isGameWon(gameState) === false).toBe(true);
  });

  it("T_213: oneMoreFactory_withNullObject", () => {
    // Given
    const referenceRules = new CreatePlayedGameRules().empty();

    // Knowing that
    expect(referenceRules.gameActions().length === 0).toBe(true);
    expect(referenceRules.victoryConditions().length === 0).toBe(true);
    expect(referenceRules.gameStopConditions().length === 0).toBe(true);
    expect(
      referenceRules.cardComparator() instanceof AlwaysFailComparisonStrategy
    ).toBe(true);

    // Given the change
    const gameName = "Random game";

    // When
    let actualRules = new CreatePlayedGameRules().withModifications(
      gameName,
      null,
      null,
      null,
      null
    );

    // Then
    expect(actualRules.gameName() === gameName).toBe(true);
    expect(
      actualRules.gameActions().length === referenceRules.gameActions().length
    ).toBe(true);
    expect(
      actualRules.victoryConditions().length ===
        referenceRules.victoryConditions().length
    ).toBe(true);
    expect(
      actualRules.gameStopConditions().length ===
        referenceRules.gameStopConditions().length
    ).toBe(true);
    expect(
      actualRules.cardComparator() instanceof AlwaysFailComparisonStrategy
    ).toBe(true);

    // Given the changes
    const actions: IGameAction[] = [new GuessCardAction()];
    const victories: IGameCondition[] = [new DidGuessACard()];

    // When
    actualRules = new CreatePlayedGameRules().withModifications(
      null,
      actions,
      victories,
      null,
      null
    );

    // Then
    expect(actualRules.gameName() === referenceRules.gameName()).toBe(true);
    expect(actualRules.gameActions()[0] instanceof GuessCardAction).toBe(true);
    expect(actualRules.victoryConditions()[0] instanceof DidGuessACard).toBe(
      true
    );
    expect(
      actualRules.gameStopConditions().length ===
        referenceRules.gameStopConditions().length
    ).toBe(true);
    expect(
      actualRules.cardComparator() instanceof AlwaysFailComparisonStrategy
    ).toBe(true);
  });

  it("T_209: theGameWasAStrategyAllAlong", () => {
    // Given
    const game = new GuessACardGame();

    // When
    // Then
    expect(game.availableActions().length === 1).toBe(true);
    expect(game.gameStopConditions().length === 1).toBe(true);
    expect(game.victoryConditions().length === 1).toBe(true);

    expect(game.availableActions()[0] instanceof GuessCardAction).toBe(true);
    expect(game.gameStopConditions()[0] instanceof DidTurnsExpire).toBe(true);
    expect(game.victoryConditions()[0] instanceof DidGuessACard).toBe(true);
  });

  it("T_210: builderPatternRevealsItself", () => {
    // Given
    const builder = new GameManagerInternalsBuilder();

    // When
    new SelectGame().changeGameRuleset(builder, "GuessACard");

    // Then
    const rules = builder.constructRuleset();

    expect(rules.cardComparator() instanceof StrictCardComparisonStrategy).toBe(true);

    expect(rules.gameActions()[0] instanceof GuessCardAction).toBe(true);
    expect(rules.gameStopConditions()[0] instanceof DidTurnsExpire).toBe(true);
    expect(rules.victoryConditions()[0] instanceof DidGuessACard).toBe(true);
  });

  it("T_211: gloryOfDeferredConstruction", () => {
    // Given
    const builder = new GameManagerInternalsBuilder();

    const commands: ICreateGameRulesCommand[] = [
      new SelectGame(),
      new GameVariant(),
    ];

    const args = ["GuessACard", "RedBlack"];

    // When
    for (let i = 0; i < commands.length; i++) {
      commands[i].changeGameRuleset(builder, args[i]);
    }

    // Then
    const rules = builder.constructRuleset();

    expect(rules.cardComparator() instanceof BlackRedColourOnlyComparisonStrategy).toBe(true);

    expect(rules.gameActions()[0] instanceof GuessCardAction).toBe(true);
    expect(rules.gameStopConditions()[0] instanceof DidTurnsExpire).toBe(true);
    expect(rules.victoryConditions()[0] instanceof DidGuessACard).toBe(true);
  });

  it("T_212: implementGuessACardCommand", () => {
    // Given
    const builder = new GameManagerInternalsBuilder();

    const commands: ICreateGameRulesCommand[] = [
      new SelectGame(),
      new GameVariant(),
      new SetDeck(),
    ];

    const args = ["GuessACard", "RedBlack", "2H,2D,3H,3D"];

    for (let i = 0; i < commands.length; i++) {
      commands[i].changeGameRuleset(builder, args[i]);
    }

    const rules = builder.constructRuleset();
    const gameState = builder.constructGameState();

    expect(QueryGameState.amountOfCardsLeft(gameState) === 4).toBe(true);

    const action = new GuessCardAction();

    // When
    // First guess is 2S (black), should come a red card, so should be a miss
    action.changeGameState(gameState, rules, "2S");

    // Then
    expect((gameState.get("Guess") as boolean) === false).toBe(true);

    // When
    // Second guess is 10H (red), should come a red card, so should be a hit
    action.changeGameState(gameState, rules, "10H");

    // Then
    expect((gameState.get("Guess") as boolean) === true).toBe(true);
  });
});
