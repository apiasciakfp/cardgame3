<?php

declare(strict_types=1);

namespace CardMultigame\Usecases\InfluenceState;

use CardMultigame\Entities\Decks\CardDeck;
use CardMultigame\Entities\GameStates\GameState;
use CardMultigame\Entities\GameStates\GameStateKeys;

final class QueryGameState
{
    public static function maximumTurns(GameState $currentState): int
    {
        $currentTurn = is_int($currentState[GameStateKeys::MaxTurns]) ? $currentState[GameStateKeys::MaxTurns] : null; // C#: as int?
        if ($currentTurn === null) throw new \InvalidArgumentException("Value cannot be null. (Parameter 'Current turn cannot be a null')");
        else return $currentTurn;
    }

    // C# (bool) unboxing throws on null / non-bool; the bool return type under strict_types does the same.
    public static function isGameWon(GameState $currentState): bool
    {
        return $currentState[GameStateKeys::IsGameWon];
    }

    public static function isGameLost(GameState $currentState): bool
    {
        return $currentState[GameStateKeys::IsGameLost];
    }

    public static function isGameFinished(GameState $currentState): bool
    {
        return self::isGameWon($currentState) || self::isGameLost($currentState);
    }

    public static function currentTurn(GameState $currentState): int
    {
        $currentTurn = is_int($currentState[GameStateKeys::CurrentTurn]) ? $currentState[GameStateKeys::CurrentTurn] : null; // C#: as int?
        if ($currentTurn === null) throw new \InvalidArgumentException("Value cannot be null. (Parameter 'Current turn cannot be a null')");
        else return $currentTurn;
    }

    public static function amountOfCardsLeft(GameState $currentState): int
    {
        return self::extractCardDeck($currentState)->cardsLeft();
    }

    public static function gameUndergoing(GameState $currentState): string
    {
        if (self::asBool($currentState[GameStateKeys::IsGameWon])) return 'Victory';
        else if (self::asBool($currentState[GameStateKeys::IsGameLost])) return 'Defeat';
        else return 'Undergoing';
    }

    public static function extractCardDeck(GameState $currentState): ?CardDeck
    {
        return $currentState[GameStateKeys::CardDeck] instanceof CardDeck ? $currentState[GameStateKeys::CardDeck] : null; // C#: as CardDeck
    }

    // C# (bool) unboxing cast inside an expression: throws (TypeError) on null / non-bool.
    private static function asBool(bool $value): bool
    {
        return $value;
    }

    private function __construct()
    {
    }
}
