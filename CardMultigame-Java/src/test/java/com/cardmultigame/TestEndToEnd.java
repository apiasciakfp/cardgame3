package com.cardmultigame;

import com.cardmultigame.entities.decks.CardDeck;
import com.cardmultigame.entities.decks.CreateCardDeck;
import com.cardmultigame.entities.gamestates.CreateGameState;
import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.entities.gamestates.GameStateKeys;
import com.cardmultigame.gamemanagers.GameManager;
import com.cardmultigame.gamemanagers.selectedrules.CreatePlayedGameRules;
import com.cardmultigame.gamemanagers.selectedrules.PlayedGameRules;
import com.cardmultigame.technical.rangens.AlwaysFirstSelector;
import com.cardmultigame.usecases.cardcomparison.StrictCardComparisonStrategy;
import com.cardmultigame.usecases.gameactions.GuessCardAction;
import com.cardmultigame.usecases.gameactions.IGameAction;
import com.cardmultigame.usecases.gameconditions.DidGuessACard;
import com.cardmultigame.usecases.gameconditions.DidTurnsExpire;
import com.cardmultigame.usecases.gameconditions.IGameCondition;
import com.cardmultigame.usecases.influencestate.QueryGameState;
import org.junit.jupiter.api.Test;
import java.util.List;
import static org.assertj.core.api.Assertions.assertThat;

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
 */
class TestEndToEnd {

    @Test
    void fullScenario_setup_miss_hit_victory_thenGameIgnoresCommands() {

        // ================================================================
        // SETUP — equivalent to:
        //   "Play GuessACard; SetDeck JH,QH,KH; SetMaxTurns 3; SETUP"
        // ================================================================

        // "Play GuessACard" selects the game, which provides:
        //   - action:    GuessCardAction  (reacts to "Guess" command)
        //   - victory:   DidGuessACard    (Guess=true → win)
        //   - stop:      DidTurnsExpire   (turn >= maxTurns → lose)
        //   - comparator: Strict          (exact rank + suit match)

        // "SetDeck JH,QH,KH" — three-card deck with deterministic draw order
        CreateCardDeck deckFactory = new CreateCardDeck();
        deckFactory.setCardSelector(new AlwaysFirstSelector());
        CardDeck deck = deckFactory.fromGivenCards("JH,QH,KH");

        // "SetMaxTurns 3"
        GameState initialState = new CreateGameState().defaultsPlusDeck(deck);
        initialState.put(GameStateKeys.MaxTurns, 3);

        // Assemble rules (what "Play GuessACard" configures internally)
        PlayedGameRules rules = new CreatePlayedGameRules().withModifications(
            "Guess a Card!",
            List.of(new GuessCardAction()),
            List.of(new DidGuessACard()),
            List.of(new DidTurnsExpire()),
            new StrictCardComparisonStrategy()
        );

        GameManager gm = new GameManager(initialState, rules);

        // ---- Verify: initial state after setup ----
        // Deck: [JH, QH, KH]. Turn 0 of 3. Game undergoing.
        GameState state = gm.currentState();
        assertThat(QueryGameState.amountOfCardsLeft(state)).isEqualTo(3);
        assertThat(QueryGameState.maximumTurns(state)).isEqualTo(3);
        assertThat(QueryGameState.currentTurn(state)).isEqualTo(0);
        assertThat(QueryGameState.isGameFinished(state)).isFalse();
        assertThat(QueryGameState.gameUndergoing(state)).isEqualTo("Undergoing");

        // ================================================================
        // TURN 1 — "Guess 2C;"
        // ================================================================
        // AlwaysFirstSelector draws JH (first card in deck).
        // Strict comparison: 2C ≠ JH → miss.
        // Deck after: [QH, KH]. Turn: 1. Game: undergoing.
        gm.executeOrders("Guess 2C;");
        state = gm.currentState();

        assertThat(state.get("Guess")).isEqualTo(false);
        assertThat(QueryGameState.currentTurn(state)).isEqualTo(1);
        assertThat(QueryGameState.amountOfCardsLeft(state)).isEqualTo(2);
        assertThat(QueryGameState.isGameFinished(state)).isFalse();
        assertThat(QueryGameState.gameUndergoing(state)).isEqualTo("Undergoing");

        // ================================================================
        // TURN 2 — "Guess QH;"
        // ================================================================
        // AlwaysFirstSelector draws QH (now first card in deck).
        // Strict comparison: QH == QH → hit!
        // Victory condition fires: Guess=true → game won.
        // Deck after: [KH]. Turn: 2. Game: Victory.
        gm.executeOrders("Guess QH;");
        state = gm.currentState();

        assertThat(state.get("Guess")).isEqualTo(true);
        assertThat(QueryGameState.currentTurn(state)).isEqualTo(2);
        assertThat(QueryGameState.amountOfCardsLeft(state)).isEqualTo(1);
        assertThat(QueryGameState.isGameFinished(state)).isTrue();
        assertThat(QueryGameState.gameUndergoing(state)).isEqualTo("Victory");

        // ================================================================
        // TURN 3 (never executes) — "Guess KH;"
        // ================================================================
        // Game is already finished. executeOrders returns immediately.
        // State is unchanged from Turn 2.
        gm.executeOrders("Guess KH;");
        state = gm.currentState();

        assertThat(QueryGameState.currentTurn(state)).isEqualTo(2);
        assertThat(QueryGameState.amountOfCardsLeft(state)).isEqualTo(1);
        assertThat(QueryGameState.gameUndergoing(state)).isEqualTo("Victory");
    }
}
