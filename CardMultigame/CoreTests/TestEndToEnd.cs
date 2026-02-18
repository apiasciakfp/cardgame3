using System.Collections.Generic;
using Core.Entities.Decks;
using Core.Entities.GameStates;
using Core.Interfaces.GameManagers;
using Core.Containers.GameRules;
using Core.GameManagers.SelectedRules;
using Core.Technical.RanGens;
using Core.Usecases.CardComparison;
using Core.Usecases.GameActions;
using Core.Usecases.GameConditions;
using Core.Usecases.InfluenceState;
using NUnit.Framework;

namespace CoreCasinoTests
{
    /// <summary>
    /// End-to-end scenario: setup → miss → hit → victory → game ignores further commands.
    ///
    /// Uses AlwaysFirstSelector (always draws first card in deck) to make the test
    /// deterministic. In production, RandomCardSelector picks a random card.
    ///
    /// Equivalent REPL session:
    ///   Input 1: "Play GuessACard; SetDeck JH,QH,KH; SetMaxTurns 3; SETUP"
    ///   Input 2: "Guess 2C;"    → miss  (drew JH, compared to 2C)
    ///   Input 3: "Guess QH;"    → hit!  (drew QH, compared to QH → Victory)
    ///   Input 4: "Guess KH;"    → ignored (game already finished)
    /// </summary>
    public class TestEndToEnd
    {
        [Test]
        public void FullScenario__Setup_Miss_Hit_Victory__ThenGameIgnoresCommands()
        {
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
            var deckFactory = new CreateCardDeck();
            deckFactory.SetCardSelector(new AlwaysFirstSelector());
            CardDeck deck = deckFactory.FromGivenCards("JH,QH,KH");

            // "SetMaxTurns 3"
            GameState initialState = new CreateGameState().DefaultsPlusDeck(deck);
            initialState[GameStateKeys.MaxTurns] = 3;

            // Assemble rules (what "Play GuessACard" configures internally)
            PlayedGameRules rules = new CreatePlayedGameRules().WithModifications(
                "Guess a Card!",
                new List<IGameAction> { new GuessCardAction() },
                new List<IGameCondition> { new DidGuessACard() },
                new List<IGameCondition> { new DidTurnsExpire() },
                new StrictCardComparisonStrategy()
            );

            GameManager gm = new GameManager(initialState, rules);

            // ---- Verify: initial state after setup ----
            // Deck: [JH, QH, KH]. Turn 0 of 3. Game undergoing.
            GameState state = gm.CurrentState();
            Assert.AreEqual(3, QueryGameState.AmountOfCardsLeft(state));
            Assert.AreEqual(3, QueryGameState.MaximumTurns(state));
            Assert.AreEqual(0, QueryGameState.CurrentTurn(state));
            Assert.IsFalse(QueryGameState.IsGameFinished(state));
            Assert.AreEqual("Undergoing", QueryGameState.GameUndergoing(state));

            // ================================================================
            // TURN 1 — "Guess 2C;"
            // ================================================================
            // AlwaysFirstSelector draws JH (first card in deck).
            // Strict comparison: 2C ≠ JH → miss.
            // Deck after: [QH, KH]. Turn: 1. Game: undergoing.
            gm.ExecuteOrders("Guess 2C;");
            state = gm.CurrentState();

            Assert.AreEqual(false, state["Guess"]);
            Assert.AreEqual(1, QueryGameState.CurrentTurn(state));
            Assert.AreEqual(2, QueryGameState.AmountOfCardsLeft(state));
            Assert.IsFalse(QueryGameState.IsGameFinished(state));
            Assert.AreEqual("Undergoing", QueryGameState.GameUndergoing(state));

            // ================================================================
            // TURN 2 — "Guess QH;"
            // ================================================================
            // AlwaysFirstSelector draws QH (now first card in deck).
            // Strict comparison: QH == QH → hit!
            // Victory condition fires: Guess=true → game won.
            // Deck after: [KH]. Turn: 2. Game: Victory.
            gm.ExecuteOrders("Guess QH;");
            state = gm.CurrentState();

            Assert.AreEqual(true, state["Guess"]);
            Assert.AreEqual(2, QueryGameState.CurrentTurn(state));
            Assert.AreEqual(1, QueryGameState.AmountOfCardsLeft(state));
            Assert.IsTrue(QueryGameState.IsGameFinished(state));
            Assert.AreEqual("Victory", QueryGameState.GameUndergoing(state));

            // ================================================================
            // TURN 3 (never executes) — "Guess KH;"
            // ================================================================
            // Game is already finished. ExecuteOrders returns immediately.
            // State is unchanged from Turn 2.
            gm.ExecuteOrders("Guess KH;");
            state = gm.CurrentState();

            Assert.AreEqual(2, QueryGameState.CurrentTurn(state));
            Assert.AreEqual(1, QueryGameState.AmountOfCardsLeft(state));
            Assert.AreEqual("Victory", QueryGameState.GameUndergoing(state));
        }
    }
}
