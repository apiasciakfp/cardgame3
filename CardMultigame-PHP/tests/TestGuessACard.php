<?php

declare(strict_types=1);

namespace CardMultigame\Tests;

use CardMultigame\GameManagers\CreateGameManager;
use CardMultigame\Usecases\InfluenceState\QueryGameState;
use PHPUnit\Framework\Attributes\Test;
use PHPUnit\Framework\TestCase;

final class TestGuessACard extends TestCase
{
    #[Test]
    public function directCardGuessingWorks_forThreeCardsDeck_failure(): void
    {
        // Given primitives
        $cards = ['JH', 'QH', 'KH'];
        $cardOutsideDeck = '2C';
        $secondSeparator = ',';
        $cardsInDeck = implode($secondSeparator, $cards);

        // Given
        $orders = 'Play GuessACard; SetDeck ' . $cardsInDeck . '; SetMaxTurns 3; ' .
            'Guess ' . $cardOutsideDeck . '; Guess ' . $cardOutsideDeck . '; Guess ' . $cardOutsideDeck;

        $gm = (new CreateGameManager())->defaultsWithOrders($orders);

        // When
        $gm->executeOrders($orders);
        $resultReceived = $gm->currentState();

        // Then
        self::assertTrue(QueryGameState::gameUndergoing($resultReceived) === 'Defeat');
        self::assertTrue(QueryGameState::maximumTurns($resultReceived) === QueryGameState::currentTurn($resultReceived));
        self::assertTrue(QueryGameState::amountOfCardsLeft($resultReceived) === 0);
    }

    #[Test]
    public function directCardGuessingWorks_forThreeCardsDeck_failure_diffSeparators(): void
    {
        // Given primitives
        $cards = ['JH', 'QH', 'KH'];
        $cardOutsideDeck = '2C';
        $secondSeparator = ';';
        $cardsInDeck = implode($secondSeparator, $cards);

        // Given
        $orders = 'Play GuessACard, SetDeck ' . $cardsInDeck . ', SetMaxTurns 3, ' .
            'Guess ' . $cardOutsideDeck . ', Guess ' . $cardOutsideDeck . ', Guess ' . $cardOutsideDeck;

        $gm = (new CreateGameManager())->defaultsWithOrders($orders);

        // When
        $gm->executeOrders($orders);
        $resultReceived = $gm->currentState();

        // Then
        self::assertTrue(QueryGameState::gameUndergoing($resultReceived) === 'Defeat');
        self::assertTrue(QueryGameState::maximumTurns($resultReceived) === QueryGameState::currentTurn($resultReceived));
        self::assertTrue(QueryGameState::amountOfCardsLeft($resultReceived) === 0);
    }

    #[Test]
    public function directCardGuessingWorks_forThreeCardsDeck_victory(): void
    {
        // Given primitives
        $cards = ['JH', 'QH', 'KH'];
        $cardInsideDeck = 'JH';
        $secondSeparator = ',';
        $cardsInDeck = implode($secondSeparator, $cards);

        // Given
        $orders = 'Play GuessACard; SetDeck ' . $cardsInDeck . '; SetMaxTurns 3; ' .
            'Guess ' . $cardInsideDeck . '; Guess ' . $cardInsideDeck . '; Guess ' . $cardInsideDeck;

        $gm = (new CreateGameManager())->defaultsWithOrders($orders);

        // When
        $gm->executeOrders($orders);
        $resultReceived = $gm->currentState();

        // Then
        self::assertTrue(QueryGameState::gameUndergoing($resultReceived) === 'Victory');
    }

    #[Test]
    public function cardRedBlackGuessingWorks_forThreeCardsOneColourDeck_missMissVictory(): void
    {
        // Given primitives
        $cards = ['JH', 'QH', 'KH'];
        $cardOutsideDeck = '2C';
        $cardInsideDeck = '2D';
        $secondSeparator = ',';
        $cardsInDeck = implode($secondSeparator, $cards);

        // Given
        $orders = 'Play GuessACard; SetDeck ' . $cardsInDeck . '; GameVariant RedBlack; ' .
            'Guess ' . $cardOutsideDeck . '; Guess ' . $cardOutsideDeck . '; Guess ' . $cardInsideDeck;

        $gm = (new CreateGameManager())->defaultsWithOrders($orders);

        // When
        $gm->executeOrders($orders);
        $resultReceived = $gm->currentState();

        // Then
        self::assertTrue(QueryGameState::gameUndergoing($resultReceived) === 'Victory');
    }
}
