<?php

declare(strict_types=1);

namespace CardMultigame\Tests;

use CardMultigame\Entities\Decks\CreateCardDeck;
use CardMultigame\Entities\GameStates\CreateGameState;
use CardMultigame\Entities\GameStates\GameStateKeys;
use CardMultigame\GameManagers\GameManager;
use CardMultigame\GameManagers\SelectedRules\CreatePlayedGameRules;
use CardMultigame\Technical\RanGens\AlwaysFirstSelector;
use CardMultigame\Usecases\CardComparison\StrictCardComparisonStrategy;
use CardMultigame\Usecases\GameActions\GuessCardAction;
use CardMultigame\Usecases\GameConditions\DidGuessACard;
use CardMultigame\Usecases\GameConditions\DidTurnsExpire;
use CardMultigame\Usecases\InfluenceState\QueryGameState;
use PHPUnit\Framework\Attributes\Test;
use PHPUnit\Framework\TestCase;

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
final class TestEndToEnd extends TestCase
{
    #[Test]
    public function fullScenario_setup_miss_hit_victory_thenGameIgnoresCommands(): void
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
        $deckFactory = new CreateCardDeck();
        $deckFactory->setCardSelector(new AlwaysFirstSelector());
        $deck = $deckFactory->fromGivenCards('JH,QH,KH');

        // "SetMaxTurns 3"
        $initialState = (new CreateGameState())->defaultsPlusDeck($deck);
        $initialState[GameStateKeys::MaxTurns] = 3;

        // Assemble rules (what "Play GuessACard" configures internally)
        $rules = (new CreatePlayedGameRules())->withModifications(
            'Guess a Card!',
            [new GuessCardAction()],
            [new DidGuessACard()],
            [new DidTurnsExpire()],
            new StrictCardComparisonStrategy()
        );

        $gm = new GameManager($initialState, $rules);

        // ---- Verify: initial state after setup ----
        // Deck: [JH, QH, KH]. Turn 0 of 3. Game undergoing.
        $state = $gm->currentState();
        self::assertSame(3, QueryGameState::amountOfCardsLeft($state));
        self::assertSame(3, QueryGameState::maximumTurns($state));
        self::assertSame(0, QueryGameState::currentTurn($state));
        self::assertFalse(QueryGameState::isGameFinished($state));
        self::assertSame('Undergoing', QueryGameState::gameUndergoing($state));

        // ================================================================
        // TURN 1 — "Guess 2C;"
        // ================================================================
        // AlwaysFirstSelector draws JH (first card in deck).
        // Strict comparison: 2C ≠ JH → miss.
        // Deck after: [QH, KH]. Turn: 1. Game: undergoing.
        $gm->executeOrders('Guess 2C;');
        $state = $gm->currentState();

        self::assertSame(false, $state['Guess']);
        self::assertSame(1, QueryGameState::currentTurn($state));
        self::assertSame(2, QueryGameState::amountOfCardsLeft($state));
        self::assertFalse(QueryGameState::isGameFinished($state));
        self::assertSame('Undergoing', QueryGameState::gameUndergoing($state));

        // ================================================================
        // TURN 2 — "Guess QH;"
        // ================================================================
        // AlwaysFirstSelector draws QH (now first card in deck).
        // Strict comparison: QH == QH → hit!
        // Victory condition fires: Guess=true → game won.
        // Deck after: [KH]. Turn: 2. Game: Victory.
        $gm->executeOrders('Guess QH;');
        $state = $gm->currentState();

        self::assertSame(true, $state['Guess']);
        self::assertSame(2, QueryGameState::currentTurn($state));
        self::assertSame(1, QueryGameState::amountOfCardsLeft($state));
        self::assertTrue(QueryGameState::isGameFinished($state));
        self::assertSame('Victory', QueryGameState::gameUndergoing($state));

        // ================================================================
        // TURN 3 (never executes) — "Guess KH;"
        // ================================================================
        // Game is already finished. executeOrders returns immediately.
        // State is unchanged from Turn 2.
        $gm->executeOrders('Guess KH;');
        $state = $gm->currentState();

        self::assertSame(2, QueryGameState::currentTurn($state));
        self::assertSame(1, QueryGameState::amountOfCardsLeft($state));
        self::assertSame('Victory', QueryGameState::gameUndergoing($state));
    }
}
