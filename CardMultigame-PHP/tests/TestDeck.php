<?php

declare(strict_types=1);

namespace CardMultigame\Tests;

use CardMultigame\Entities\Cards\CreateCards;
use CardMultigame\Entities\Decks\CreateCardDeck;
use CardMultigame\Usecases\CardComparison\StrictCardComparisonStrategy;
use PHPUnit\Framework\Attributes\Test;
use PHPUnit\Framework\TestCase;

final class TestDeck extends TestCase
{
    #[Test]
    public function drawCardFromDeck_randomly_5CardsUntil0Left(): void
    {
        // Given
        $cardSigils = ['9H', '10H', 'JH', 'QH', 'KH'];
        $separator = ',';
        $cardsInDeck = implode($separator, $cardSigils);

        $cards = (new CreateCards())->createCollection($cardsInDeck);
        $deck = (new CreateCardDeck())->fromGivenCards($cardsInDeck);

        // Expecting
        $lengthInDeck = 0;
        $lengthOfDrawnCards = count($cards);

        // When
        $drawnCards = [];
        for ($i = 0; $i < count($cardSigils); $i++) {
            $drawnCards[] = $deck->drawRandomCard();
        }

        // Then
        $cardsRemaining = $deck->allCards();

        self::assertTrue(count($cardsRemaining) === $lengthInDeck);
        self::assertTrue(count($drawnCards) === $lengthOfDrawnCards);
    }

    #[Test]
    public function createDeck_withStandardCards9ToAWith4Colours(): void
    {
        // Given
        // Expecting
        $cardCountExpected = 24;

        // When
        $deck = (new CreateCardDeck())->simple9ToAWith4Colours();

        // Then
        $cardsReceived = $deck->allCards();

        self::assertTrue(count($cardsReceived) === $cardCountExpected);
    }

    #[Test]
    public function createDeck_with3SetCards_inCommaFormat(): void
    {
        // Given
        $cards = ['JH', 'QH', 'KH'];
        $separator = ',';
        $cardsInDeck = implode($separator, $cards);

        // Expecting
        $cardsExpected = (new CreateCards())->createCollection($cardsInDeck);

        // When
        $deck = (new CreateCardDeck())->fromGivenCards($cardsInDeck);

        // Then
        $cardsReceived = $deck->allCards();

        self::assertTrue(count($cardsExpected) === count($cardsReceived));

        for ($i = 0; $i < count($cardsExpected); $i++) {
            self::assertTrue((new StrictCardComparisonStrategy())->areTheSame($cardsExpected[$i], $cardsReceived[$i]));
        }
    }
}
