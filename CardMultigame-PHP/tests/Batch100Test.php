<?php

declare(strict_types=1);

namespace CardMultigame\Tests;

use CardMultigame\Entities\Cards\Card;
use CardMultigame\Entities\Cards\CreateCards;
use CardMultigame\Entities\Decks\CardDeck;
use CardMultigame\Entities\Decks\CreateCardDeck;
use CardMultigame\Entities\Games\Guessing\GuessACardGame;
use CardMultigame\Technical\RanGens\AlwaysFirstSelector;
use CardMultigame\Technical\Parsers\SelectedParser;
use CardMultigame\Technical\RanGens\AlwaysLastSelector;
use CardMultigame\Usecases\CardComparison\BlackRedColourOnlyComparisonStrategy;
use CardMultigame\Usecases\CardComparison\ColourCardComparisonStrategy;
use CardMultigame\Usecases\CardComparison\CreateCardComparisonStrategy;
use CardMultigame\Usecases\CardComparison\RankCardComparisonStrategy;
use CardMultigame\Usecases\CardComparison\StrictCardComparisonStrategy;
use PHPUnit\Framework\Attributes\Test;
use PHPUnit\Framework\TestCase;

final class Batch100Test extends TestCase
{
    #[Test]
    public function t108_letsPrepareTheStrategyForTheFuture(): void
    {
        // Given - nothing
        // When
        $selectedStrategy = (new GuessACardGame())->cardComparisonStrategy();

        // Then
        self::assertTrue($selectedStrategy instanceof StrictCardComparisonStrategy);
    }

    #[Test]
    public function t101_strategyBasics(): void
    {
        $card1 = new Card('J', 'H');
        $identicalCard = new Card('J', 'H');
        $differentCard = new Card('K', 'H');

        $areTheSameWithIdentical = (new StrictCardComparisonStrategy())->areTheSame($card1, $identicalCard);
        $areTheSameWithDifferent = (new StrictCardComparisonStrategy())->areTheSame($card1, $differentCard);

        self::assertTrue($areTheSameWithIdentical);
        self::assertFalse($areTheSameWithDifferent);
    }

    #[Test]
    public function t102_implementYourOwnStrategy(): void
    {
        $card1 = new Card('J', 'H');
        $identicalCard = new Card('2', 'H');
        $differentCard = new Card('J', 'D');

        $areTheSameWithIdentical = (new ColourCardComparisonStrategy())->areTheSame($card1, $identicalCard);
        $areTheSameWithDifferent = (new ColourCardComparisonStrategy())->areTheSame($card1, $differentCard);

        self::assertTrue($areTheSameWithIdentical);
        self::assertFalse($areTheSameWithDifferent);
    }

    #[Test]
    public function t103_implementTheBlackRedStrategy(): void
    {
        $reference = new Card('2', 'H');
        $identical1 = new Card('2', 'H');
        $identical2 = new Card('7', 'D');
        $different1 = new Card('2', 'S');
        $different2 = new Card('Q', 'C');

        self::assertTrue((new BlackRedColourOnlyComparisonStrategy())->areTheSame($reference, $identical1));
        self::assertTrue((new BlackRedColourOnlyComparisonStrategy())->areTheSame($reference, $identical2));
        self::assertFalse((new BlackRedColourOnlyComparisonStrategy())->areTheSame($reference, $different1));
        self::assertFalse((new BlackRedColourOnlyComparisonStrategy())->areTheSame($reference, $different2));
    }

    #[Test]
    public function t104_powerOfPolymorphism(): void
    {
        $card1 = new Card('J', 'H');
        $card2 = new Card('A', 'H');

        $strategy = new StrictCardComparisonStrategy();
        self::assertFalse($strategy->areTheSame($card1, $card2));

        $strategy = new ColourCardComparisonStrategy();
        self::assertTrue($strategy->areTheSame($card1, $card2));

        $strategy = new RankCardComparisonStrategy();
        self::assertFalse($strategy->areTheSame($card1, $card2));

        $strategy = new BlackRedColourOnlyComparisonStrategy();
        self::assertTrue($strategy->areTheSame($card1, $card2));
    }

    #[Test]
    public function t105_factoryMethod_oneStrategyOnly(): void
    {
        $card1 = new Card('J', 'H');
        $card2 = new Card('A', 'H');

        $strategy = (new CreateCardComparisonStrategy())->create('colour');
        $areTheSame = $strategy->areTheSame($card1, $card2);

        self::assertTrue($areTheSame);
    }

    #[Test]
    public function t106_factoryMethod_allStrategies(): void
    {
        $card1 = new Card('J', 'H');
        $card2 = new Card('A', 'H');

        $strategy = (new CreateCardComparisonStrategy())->create('strict');
        self::assertFalse($strategy->areTheSame($card1, $card2));

        $strategy = (new CreateCardComparisonStrategy())->create('colour');
        self::assertTrue($strategy->areTheSame($card1, $card2));

        $strategy = (new CreateCardComparisonStrategy())->create('rank');
        self::assertFalse($strategy->areTheSame($card1, $card2));

        $strategy = (new CreateCardComparisonStrategy())->create('blackred');
        self::assertTrue($strategy->areTheSame($card1, $card2));
    }

    #[Test]
    public function t107_nullObjectWeAllLove(): void
    {
        $card1 = new Card('J', 'H');
        $card2 = new Card('A', 'H');

        $strategies = [
            (new CreateCardComparisonStrategy())->create('THIS IS A TYPO!'),
            (new CreateCardComparisonStrategy())->create(''),
            (new CreateCardComparisonStrategy())->create('al/fdkafklfhflsdhflhffhfh'),
            (new CreateCardComparisonStrategy())->create('f;lff;kklfs;df'),
            (new CreateCardComparisonStrategy())->create("don't else-if those cases please..."),
        ];

        foreach ($strategies as $strategy) {
            self::assertFalse($strategy->areTheSame($card1, $card2));
        }
    }

    #[Test]
    public function t109_cardDeckNeedsDifferentCreationWays(): void
    {
        $cardsBetween2A = 13;
        $cardColours = 4;
        $totalCards = $cardsBetween2A * $cardColours;

        $lowCard = new Card('2', 'C');
        $highCard = new Card('K', 'H');

        $deck = (new CreateCardDeck())->simple2ToAWith4Colours();
        $allCards = $deck->allCards();

        $foundSmall = false;
        $foundLarge = false;

        foreach ($allCards as $card) {
            if ((new StrictCardComparisonStrategy())->areTheSame($card, $lowCard)) $foundSmall = true;
            if ((new StrictCardComparisonStrategy())->areTheSame($card, $highCard)) $foundLarge = true;
        }

        self::assertTrue($foundSmall);
        self::assertTrue($foundLarge);
    }

    #[Test]
    public function t110_parsers_ofCourseParsers(): void
    {
        // Case1: ';' as main delimiter, ',' as second.
        $ordersExpected = [
            ['Play', 'GuessACard'],
            ['SetDeck', 'JH, QH, KH'],
            ['StartGame', ''],
            ['Guess', 'JH'],
            ['Guess', 'QH'],
        ];
        $ordersString = 'Play GuessACard; SetDeck JH, QH, KH; StartGame; Guess JH; Guess QH';
        $ordersReceived = (new SelectedParser())->properlyParse($ordersString);
        for ($i = 0; $i < count($ordersExpected); $i++) {
            self::assertSame($ordersExpected[$i], $ordersReceived[$i]);
        }

        // Case2: ',' as main delimiter, ';' as second.
        $ordersExpected = [
            ['Play', 'GuessACard'],
            ['SetDeck', 'JH; QH; KH'],
            ['StartGame', ''],
            ['Guess', 'JH'],
            ['Guess', 'QH'],
        ];
        $ordersString = 'Play GuessACard, SetDeck JH; QH; KH, StartGame, Guess JH, Guess QH';
        $ordersReceived = (new SelectedParser())->properlyParse($ordersString);
        for ($i = 0; $i < count($ordersExpected); $i++) {
            self::assertSame($ordersExpected[$i], $ordersReceived[$i]);
        }

        // Case3: '-' as main delimiter, ',' as second.
        $ordersExpected = [
            ['Play', 'GuessACard'],
            ['SetDeck', 'JH, QH, KH'],
            ['StartGame', ''],
            ['Guess', 'JH'],
            ['Guess', 'QH'],
        ];
        $ordersString = 'Play GuessACard - SetDeck JH, QH, KH - StartGame - Guess JH - Guess QH';
        $ordersReceived = (new SelectedParser())->properlyParse($ordersString);
        for ($i = 0; $i < count($ordersExpected); $i++) {
            self::assertSame($ordersExpected[$i], $ordersReceived[$i]);
        }
    }

    #[Test]
    public function t111_cardDeckCanHaveConfiguredRandomGenerator_first(): void
    {
        // Given, Expected
        $selector = new AlwaysFirstSelector();
        $expectedCards = (new CreateCards())->createCollection('9H, 10H, 9C, 10C, AD');

        $copiedList = $expectedCards;
        $deck = new CardDeck($selector, $copiedList);

        // When
        $actualCards = [];
        for ($i = 0; $i < 5; $i++) {
            $actualCards[] = $deck->drawRandomCard();
        }

        // Then
        for ($i = 0; $i < 5; $i++) {
            self::assertTrue($expectedCards[$i]->colour() === $actualCards[$i]->colour());
            self::assertTrue($expectedCards[$i]->rank() === $actualCards[$i]->rank());
        }
    }

    #[Test]
    public function t112_cardDeckCanHaveConfiguredRandomGenerator_last(): void
    {
        // Given, Expected
        $selector = new AlwaysLastSelector();
        $expectedCards = (new CreateCards())->createCollection('9H, 10H, 9C, 10C, AD');

        $copiedList = $expectedCards;
        $deck = new CardDeck($selector, $copiedList);

        // When
        $actualCards = [];
        for ($i = 0; $i < 5; $i++) {
            $actualCards[] = $deck->drawRandomCard();
        }

        // Then
        for ($i = 0; $i < 5; $i++) {
            self::assertTrue($expectedCards[4 - $i]->colour() === $actualCards[$i]->colour());
            self::assertTrue($expectedCards[4 - $i]->rank() === $actualCards[$i]->rank());
        }
    }

    #[Test]
    public function t113_cardDeckFactory_canReconfigureRandomGenerator(): void
    {
        // Given
        $inputCardSigils = 'JS, QH, KD, AC';

        // Expected
        $expectedCards = (new CreateCards())->createCollection($inputCardSigils);

        // Given: look at this CLOSELY
        $creator = new CreateCardDeck();

        $creator->setCardSelector(new AlwaysFirstSelector());
        $deckWithAlwaysFirst = $creator->fromGivenCards($inputCardSigils);

        // When
        $actualFirstCards = [];
        for ($i = 0; $i < 4; $i++) {
            $actualFirstCards[] = $deckWithAlwaysFirst->drawRandomCard();
        }

        // Then
        for ($i = 0; $i < 4; $i++) {
            self::assertTrue($expectedCards[$i]->colour() === $actualFirstCards[$i]->colour());
            self::assertTrue($expectedCards[$i]->rank() === $actualFirstCards[$i]->rank());
        }

        // Given again
        $creator->setCardSelector(new AlwaysLastSelector());
        $deckWithAlwaysLast = $creator->fromGivenCards($inputCardSigils);

        // When
        $actualLastCards = [];
        for ($i = 0; $i < 4; $i++) {
            $actualLastCards[] = $deckWithAlwaysLast->drawRandomCard();
        }

        // Then
        for ($i = 0; $i < 4; $i++) {
            self::assertTrue($expectedCards[3 - $i]->colour() === $actualLastCards[$i]->colour());
            self::assertTrue($expectedCards[3 - $i]->rank() === $actualLastCards[$i]->rank());
        }
    }
}
