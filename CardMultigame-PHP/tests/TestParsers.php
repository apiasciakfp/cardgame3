<?php

declare(strict_types=1);

namespace CardMultigame\Tests;

use CardMultigame\Technical\Parsers\SelectedParser;
use PHPUnit\Framework\Attributes\Test;
use PHPUnit\Framework\TestCase;

final class TestParsers extends TestCase
{
    #[Test]
    public function parserProperlySelected_semicolonSeparator(): void
    {
        // Expecting
        $ordersExpected = [
            ['Play', 'GuessACard'],
            ['SetDeck', 'JH, QH, KH'],
            ['StartGame', ''],
            ['Guess', 'JH'],
            ['Guess', 'QH'],
        ];

        // Given
        $ordersString = 'Play GuessACard; SetDeck JH, QH, KH; StartGame; Guess JH; Guess QH';

        // When
        $ordersReceived = (new SelectedParser())->properlyParse($ordersString);

        // Then
        for ($i = 0; $i < count($ordersExpected); $i++) {
            self::assertSame($ordersExpected[$i], $ordersReceived[$i]);
        }
    }

    #[Test]
    public function parserProperlySelected_commaSeparator(): void
    {
        // Expecting
        $ordersExpected = [
            ['Play', 'GuessACard'],
            ['SetDeck', 'JH; QH; KH'],
            ['StartGame', ''],
            ['Guess', 'JH'],
            ['Guess', 'QH'],
        ];

        // Given
        $ordersString = 'Play GuessACard, SetDeck JH; QH; KH, StartGame, Guess JH, Guess QH';

        // When
        $ordersReceived = (new SelectedParser())->properlyParse($ordersString);

        // Then
        for ($i = 0; $i < count($ordersExpected); $i++) {
            self::assertSame($ordersExpected[$i], $ordersReceived[$i]);
        }
    }
}
