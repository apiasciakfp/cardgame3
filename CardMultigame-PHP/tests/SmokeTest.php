<?php

declare(strict_types=1);

namespace CardMultigame\Tests;

use CardMultigame\Entities\Cards\Card;
use PHPUnit\Framework\Attributes\Test;
use PHPUnit\Framework\TestCase;

/**
 * Port of Java SmokeTest, re-targeted to PHP (runtime version + scaffold wired).
 */
final class SmokeTest extends TestCase
{
    #[Test]
    public function phpVersionIs83(): void
    {
        // Java original asserted the runtime was Java 21; here we assert PHP 8.3.
        self::assertStringStartsWith('8.3', PHP_VERSION);
    }

    #[Test]
    public function scaffoldIsWired(): void
    {
        // Java original asserted the "CardMultigame" name was non-empty; here we assert
        // that an autoloaded CardMultigame class resolves.
        self::assertTrue(class_exists(Card::class));
    }
}
