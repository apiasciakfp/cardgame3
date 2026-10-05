<?php

declare(strict_types=1);

namespace CardMultigame\Tests;

use CardMultigame\Entities\Decks\CreateCardDeck;
use CardMultigame\Entities\Games\Guessing\GuessACardGame;
use CardMultigame\Entities\GameStates\CreateGameState;
use CardMultigame\Entities\GameStates\GameStateKeys;
use CardMultigame\GameManagers\GameManagerInternalsBuilder;
use CardMultigame\GameManagers\SelectedRules\CreatePlayedGameRules;
use CardMultigame\GameManagers\SelectedRules\CreationCommands\GameVariant;
use CardMultigame\GameManagers\SelectedRules\CreationCommands\SelectGame;
use CardMultigame\GameManagers\SelectedRules\CreationCommands\SetDeck;
use CardMultigame\Usecases\CardComparison\AlwaysFailComparisonStrategy;
use CardMultigame\Usecases\CardComparison\BlackRedColourOnlyComparisonStrategy;
use CardMultigame\Usecases\CardComparison\StrictCardComparisonStrategy;
use CardMultigame\Usecases\GameActions\Add10COrDrawACard;
use CardMultigame\Usecases\GameActions\AddQueenOfHeartsToDeck;
use CardMultigame\Usecases\GameActions\CreateGameActions;
use CardMultigame\Usecases\GameActions\DrawSingleCardAction;
use CardMultigame\Usecases\GameActions\GuessCardAction;
use CardMultigame\Usecases\GameConditions\DidGuessACard;
use CardMultigame\Usecases\GameConditions\DidTurnsExpire;
use CardMultigame\Usecases\InfluenceState\ModifyGameState;
use CardMultigame\Usecases\InfluenceState\QueryGameState;
use PHPUnit\Framework\Attributes\Test;
use PHPUnit\Framework\TestCase;

final class Batch200Test extends TestCase
{
    #[Test]
    public function t201_gentleIntroductionToCommand(): void
    {
        // Tutorial: how to extract the CardDeck from the GameState
        $tutorialState = (new CreateGameState())->defaultsWithFullDeck();
        $tutorialDeck = QueryGameState::extractCardDeck($tutorialState);
        $tutorialDeck->drawRandomCard();

        // Given
        $deck = (new CreateCardDeck())->fromGivenCards('2H, 3H, 4H');
        $gameState = (new CreateGameState())->defaultsPlusDeck($deck);

        // Expected:
        self::assertTrue(QueryGameState::amountOfCardsLeft($gameState) === 3);
        $amountOfCardsAfterDrawingOne = QueryGameState::amountOfCardsLeft($gameState) - 1;

        // When
        (new DrawSingleCardAction())->changeGameState($gameState, null, null);

        // Then
        self::assertTrue(QueryGameState::amountOfCardsLeft($gameState) === $amountOfCardsAfterDrawingOne);
    }

    #[Test]
    public function t202_addSome_QH_intoTheCardDeck(): void
    {
        // Given
        $deck = (new CreateCardDeck())->fromGivenCards('2H, 3H, 4H');
        $gameState = (new CreateGameState())->defaultsPlusDeck($deck);

        $actions = [
            new AddQueenOfHeartsToDeck(),
            new AddQueenOfHeartsToDeck(),
            new AddQueenOfHeartsToDeck(),
            new AddQueenOfHeartsToDeck(),
            new AddQueenOfHeartsToDeck(),
        ];

        // Expected:
        self::assertTrue(QueryGameState::amountOfCardsLeft($gameState) === 3);
        $amountOfCardsAfterDrawingOne = QueryGameState::amountOfCardsLeft($gameState) + count($actions);

        // When
        foreach ($actions as $action) {
            $action->changeGameState($gameState, null, null);
        }

        // Then
        self::assertTrue(QueryGameState::amountOfCardsLeft($gameState) === $amountOfCardsAfterDrawingOne);

        $retrievedDeck = QueryGameState::extractCardDeck($gameState);

        for ($i = 0; $i < 5; $i++) {
            $card = $retrievedDeck->drawLastAddedCard();
            self::assertTrue($card->rank() === 'Q');
            self::assertTrue($card->colour() === 'H');
        }
    }

    #[Test]
    public function t203_chainSomeCommands(): void
    {
        // Given
        $deck = (new CreateCardDeck())->fromGivenCards('2H, 3H, 4H');
        $gameState = (new CreateGameState())->defaultsPlusDeck($deck);

        $actions = [
            new DrawSingleCardAction(),
            new DrawSingleCardAction(),
            new DrawSingleCardAction(),     // now it should be empty
            new AddQueenOfHeartsToDeck(),
            new AddQueenOfHeartsToDeck(),
            new Add10COrDrawACard(),        // should add +1 card, because even
            new Add10COrDrawACard(),        // should draw a card, because odd
        ];

        // Expected:
        self::assertTrue(QueryGameState::amountOfCardsLeft($gameState) === 3);
        $amountOfCardsAfterDrawingOne = 2;

        // When
        foreach ($actions as $action) {
            $action->changeGameState($gameState, null, null);
        }

        // Then
        self::assertTrue(QueryGameState::amountOfCardsLeft($gameState) === $amountOfCardsAfterDrawingOne);
    }

    #[Test]
    public function t204_factorizeMe(): void
    {
        // Given
        $deck = (new CreateCardDeck())->fromGivenCards('2H, 3H, 4H');
        $gameState = (new CreateGameState())->defaultsPlusDeck($deck);

        $actionsToPerform = 'drawSingleCard, drawSingleCard, drawSingleCard, addQH, addQH, ' .
            'add10cOrDraw, add10cOrDraw';
        $actions = (new CreateGameActions())->havingOrders($actionsToPerform);

        // Expected:
        self::assertTrue(QueryGameState::amountOfCardsLeft($gameState) === 3);
        $amountOfCardsAfterDrawingOne = 2;

        // When
        foreach ($actions as $action) {
            $action->changeGameState($gameState, null, null);
        }

        // Then
        self::assertTrue(QueryGameState::amountOfCardsLeft($gameState) === $amountOfCardsAfterDrawingOne);
    }

    #[Test]
    public function t205_commandsCanCommunicateViaContext(): void
    {
        // Tutorial
        $tutorialState = (new CreateGameState())->default();
        self::assertTrue($tutorialState['SpecificKey'] === null);
        $tutorialState['SpecificKey'] = 'Capybara';
        self::assertTrue($tutorialState['SpecificKey'] === 'Capybara');

        // Given
        $deck = (new CreateCardDeck())->fromGivenCards('2H, 3H, 4H');
        $gameState = (new CreateGameState())->defaultsPlusDeck($deck);

        $actionsToPerform = 'drawSingleCard, drawSingleCard, drawSingleCard';
        $actions = (new CreateGameActions())->havingOrders($actionsToPerform);

        // Expected:
        self::assertTrue(QueryGameState::amountOfCardsLeft($gameState) === 3);

        // When
        foreach ($actions as $action) {
            $action->changeGameState($gameState, null, null);
        }

        // Then
        self::assertTrue($gameState['Guess'] === true);
    }

    #[Test]
    public function t206_queryGameState_cannotChangeAThing(): void
    {
        // Given
        $gameState = (new CreateGameState())->default();
        $gameState[GameStateKeys::IsGameWon] = false;
        $gameState[GameStateKeys::IsGameLost] = false;

        // When
        // Then
        self::assertTrue(QueryGameState::isGameWon($gameState) === false);
        self::assertTrue(QueryGameState::isGameLost($gameState) === false);
    }

    #[Test]
    public function t207_modifyGameState_canChangeQuiteALot(): void
    {
        // Given
        $gameState = (new CreateGameState())->default();
        $gameState[GameStateKeys::IsGameWon] = false;
        $gameState[GameStateKeys::IsGameLost] = false;

        // Given: making sure
        self::assertTrue(QueryGameState::isGameWon($gameState) === false);
        self::assertTrue(QueryGameState::isGameLost($gameState) === false);

        // When
        ModifyGameState::declareGameToBeWon($gameState);
        ModifyGameState::declareGameToBeLost($gameState);

        // Then
        self::assertTrue(QueryGameState::isGameWon($gameState) === true);
        self::assertTrue(QueryGameState::isGameLost($gameState) === true);
    }

    #[Test]
    public function t208_winConditionLossCondition(): void
    {
        // Given
        $gameState = (new CreateGameState())->defaultsWithFullDeck();

        $actionsToPerform = 'drawSingleCard, drawSingleCard';
        $actions = (new CreateGameActions())->havingOrders($actionsToPerform);

        $conditions = [
            new DidGuessACard(), new DidTurnsExpire(),
        ];

        // When
        do {
            foreach ($actions as $action) {
                $action->changeGameState($gameState, null, null);
            }

            foreach ($conditions as $condition) {
                $condition->checkAndUpdate($gameState);
            }
        } while (QueryGameState::isGameFinished($gameState) === false);

        // Then
        self::assertTrue(QueryGameState::isGameLost($gameState) === true);
        self::assertTrue(QueryGameState::isGameWon($gameState) === false);
    }

    #[Test]
    public function t213_oneMoreFactory_withNullObject(): void
    {
        // Given
        $referenceRules = (new CreatePlayedGameRules())->empty();

        // Knowing that
        self::assertTrue(count($referenceRules->gameActions()) === 0);
        self::assertTrue(count($referenceRules->victoryConditions()) === 0);
        self::assertTrue(count($referenceRules->gameStopConditions()) === 0);
        self::assertTrue($referenceRules->cardComparator() instanceof AlwaysFailComparisonStrategy);

        // Given the change
        $gameName = 'Random game';

        // When
        $actualRules = (new CreatePlayedGameRules())->withModifications($gameName, null, null, null, null);

        // Then
        self::assertTrue($actualRules->gameName() === $gameName);
        self::assertTrue(count($actualRules->gameActions()) === count($referenceRules->gameActions()));
        self::assertTrue(count($actualRules->victoryConditions()) === count($referenceRules->victoryConditions()));
        self::assertTrue(count($actualRules->gameStopConditions()) === count($referenceRules->gameStopConditions()));
        self::assertTrue($actualRules->cardComparator() instanceof AlwaysFailComparisonStrategy);

        // Given the changes
        $actions = [new GuessCardAction()];
        $victories = [new DidGuessACard()];

        // When
        $actualRules = (new CreatePlayedGameRules())->withModifications(null, $actions, $victories, null, null);

        // Then
        self::assertTrue($actualRules->gameName() === $referenceRules->gameName());
        self::assertTrue($actualRules->gameActions()[0] instanceof GuessCardAction);
        self::assertTrue($actualRules->victoryConditions()[0] instanceof DidGuessACard);
        self::assertTrue(count($actualRules->gameStopConditions()) === count($referenceRules->gameStopConditions()));
        self::assertTrue($actualRules->cardComparator() instanceof AlwaysFailComparisonStrategy);
    }

    #[Test]
    public function t209_theGameWasAStrategyAllAlong(): void
    {
        // Given
        $game = new GuessACardGame();

        // When
        // Then
        self::assertTrue(count($game->availableActions()) === 1);
        self::assertTrue(count($game->gameStopConditions()) === 1);
        self::assertTrue(count($game->victoryConditions()) === 1);

        self::assertTrue($game->availableActions()[0] instanceof GuessCardAction);
        self::assertTrue($game->gameStopConditions()[0] instanceof DidTurnsExpire);
        self::assertTrue($game->victoryConditions()[0] instanceof DidGuessACard);
    }

    #[Test]
    public function t210_builderPatternRevealsItself(): void
    {
        // Given
        $builder = new GameManagerInternalsBuilder();

        // When
        (new SelectGame())->changeGameRuleset($builder, 'GuessACard');

        // Then
        $rules = $builder->constructRuleset();

        self::assertTrue($rules->cardComparator() instanceof StrictCardComparisonStrategy);

        self::assertTrue($rules->gameActions()[0] instanceof GuessCardAction);
        self::assertTrue($rules->gameStopConditions()[0] instanceof DidTurnsExpire);
        self::assertTrue($rules->victoryConditions()[0] instanceof DidGuessACard);
    }

    #[Test]
    public function t211_gloryOfDeferredConstruction(): void
    {
        // Given
        $builder = new GameManagerInternalsBuilder();

        $commands = [
            new SelectGame(), new GameVariant(),
        ];

        $arguments = ['GuessACard', 'RedBlack'];

        // When
        for ($i = 0; $i < count($commands); $i++) {
            $commands[$i]->changeGameRuleset($builder, $arguments[$i]);
        }

        // Then
        $rules = $builder->constructRuleset();

        self::assertTrue($rules->cardComparator() instanceof BlackRedColourOnlyComparisonStrategy);

        self::assertTrue($rules->gameActions()[0] instanceof GuessCardAction);
        self::assertTrue($rules->gameStopConditions()[0] instanceof DidTurnsExpire);
        self::assertTrue($rules->victoryConditions()[0] instanceof DidGuessACard);
    }

    #[Test]
    public function t212_implementGuessACardCommand(): void
    {
        // Given
        $builder = new GameManagerInternalsBuilder();

        $commands = [
            new SelectGame(), new GameVariant(), new SetDeck(),
        ];

        $arguments = ['GuessACard', 'RedBlack', '2H,2D,3H,3D'];

        for ($i = 0; $i < count($commands); $i++) {
            $commands[$i]->changeGameRuleset($builder, $arguments[$i]);
        }

        $rules = $builder->constructRuleset();
        $gameState = $builder->constructGameState();

        self::assertTrue(QueryGameState::amountOfCardsLeft($gameState) === 4);

        $action = new GuessCardAction();

        // When
        // First guess is 2S (black), should come a red card, so should be a miss
        $action->changeGameState($gameState, $rules, '2S');

        // Then
        self::assertTrue($gameState['Guess'] === false);

        // When
        // Second guess is 10H (red), should come a red card, so should be a hit
        $action->changeGameState($gameState, $rules, '10H');

        // Then
        self::assertTrue($gameState['Guess'] === true);
    }
}
