import { describe, it, expect } from "vitest";
import { CreateCardDeck } from "../src/entities/decks/CreateCardDeck.js";
import { CreateGameState } from "../src/entities/gamestates/CreateGameState.js";
import { GameStateKeys } from "../src/entities/gamestates/GameStateKeys.js";
import { GameManager } from "../src/gamemanagers/GameManager.js";
import { CreatePlayedGameRules } from "../src/gamemanagers/selectedrules/CreatePlayedGameRules.js";
import { AlwaysFirstSelector } from "../src/technical/rangens/AlwaysFirstSelector.js";
import { StrictCardComparisonStrategy } from "../src/usecases/cardcomparison/StrictCardComparisonStrategy.js";
import { GuessCardAction } from "../src/usecases/gameactions/GuessCardAction.js";
import { DidGuessACard } from "../src/usecases/gameconditions/DidGuessACard.js";
import { DidTurnsExpire } from "../src/usecases/gameconditions/DidTurnsExpire.js";
import * as QueryGameState from "../src/usecases/influencestate/QueryGameState.js";

/**
 * End-to-end scenario: setup → miss → hit → victory → game ignores further commands.
 *
 * Uses AlwaysFirstSelector (always draws first card in deck) to make the test
 * deterministic. In production, RandomCardSelector picks a random card.
 *
 * Equivalent REPL session:
 *   Input 1: "Play GuessACard; SetDeck JH,QH,KH; SetMaxTurns 3; SETUP"
 *   Input 2: "Guess 2C;"    → miss  (drew JH, compared to 2C)
 *   Input 3: "Guess QH;"    → hit!  (drew QH, compared to QH → Victory)
 *   Input 4: "Guess KH;"    → ignored (game already finished)
 *
 * Port of the C# / Java / Python TestEndToEnd, via the manual construction path.
 */
describe("TestEndToEnd", () => {
  it("fullScenario_setup_miss_hit_victory_thenGameIgnoresCommands", () => {
    // ================================================================
    // SETUP — equivalent to:
    //   "Play GuessACard; SetDeck JH,QH,KH; SetMaxTurns 3; SETUP"
    // ================================================================

    // "Play GuessACard" selects the game, which provides:
    //   - action:     GuessCardAction  (reacts to "Guess" command)
    //   - victory:    DidGuessACard    (Guess=true → win)
    //   - stop:       DidTurnsExpire   (turn >= maxTurns → lose)
    //   - comparator: Strict           (exact rank + suit match)

    // "SetDeck JH,QH,KH" — three-card deck with deterministic draw order
    const deckFactory = new CreateCardDeck();
    deckFactory.setCardSelector(new AlwaysFirstSelector());
    const deck = deckFactory.fromGivenCards("JH,QH,KH");

    // "SetMaxTurns 3"
    const initialState = new CreateGameState().defaultsPlusDeck(deck);
    initialState.set(GameStateKeys.MaxTurns, 3);

    // Assemble rules (what "Play GuessACard" configures internally)
    const rules = new CreatePlayedGameRules().withModifications(
      "Guess a Card!",
      [new GuessCardAction()],
      [new DidGuessACard()],
      [new DidTurnsExpire()],
      new StrictCardComparisonStrategy()
    );

    const gm = new GameManager(initialState, rules);

    // ---- Verify: initial state after setup ----
    // Deck: [JH, QH, KH]. Turn 0 of 3. Game undergoing.
    let state = gm.currentState();
    expect(QueryGameState.amountOfCardsLeft(state)).toBe(3);
    expect(QueryGameState.maximumTurns(state)).toBe(3);
    expect(QueryGameState.currentTurn(state)).toBe(0);
    expect(QueryGameState.isGameFinished(state)).toBe(false);
    expect(QueryGameState.gameUndergoing(state)).toBe("Undergoing");

    // ================================================================
    // TURN 1 — "Guess 2C;"
    // ================================================================
    // AlwaysFirstSelector draws JH (first card in deck).
    // Strict comparison: 2C ≠ JH → miss.
    // Deck after: [QH, KH]. Turn: 1. Game: undergoing.
    gm.executeOrders("Guess 2C;");
    state = gm.currentState();

    expect(state.get("Guess")).toBe(false);
    expect(QueryGameState.currentTurn(state)).toBe(1);
    expect(QueryGameState.amountOfCardsLeft(state)).toBe(2);
    expect(QueryGameState.isGameFinished(state)).toBe(false);
    expect(QueryGameState.gameUndergoing(state)).toBe("Undergoing");

    // ================================================================
    // TURN 2 — "Guess QH;"
    // ================================================================
    // AlwaysFirstSelector draws QH (now first card in deck).
    // Strict comparison: QH == QH → hit!
    // Victory condition fires: Guess=true → game won.
    // Deck after: [KH]. Turn: 2. Game: Victory.
    gm.executeOrders("Guess QH;");
    state = gm.currentState();

    expect(state.get("Guess")).toBe(true);
    expect(QueryGameState.currentTurn(state)).toBe(2);
    expect(QueryGameState.amountOfCardsLeft(state)).toBe(1);
    expect(QueryGameState.isGameFinished(state)).toBe(true);
    expect(QueryGameState.gameUndergoing(state)).toBe("Victory");

    // ================================================================
    // TURN 3 (never executes) — "Guess KH;"
    // ================================================================
    // Game is already finished. executeOrders returns immediately.
    // State is unchanged from Turn 2.
    gm.executeOrders("Guess KH;");
    state = gm.currentState();

    expect(QueryGameState.currentTurn(state)).toBe(2);
    expect(QueryGameState.amountOfCardsLeft(state)).toBe(1);
    expect(QueryGameState.gameUndergoing(state)).toBe("Victory");
  });
});
