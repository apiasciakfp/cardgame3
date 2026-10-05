<?php

declare(strict_types=1);

namespace CardMultigame\Entities\GameStates;

final class GameStateKeys
{
    public const CurrentTurn = 'CurrentTurnNumber';
    public const MaxTurns = 'MaximumTurns';
    public const IsGameWon = 'IsGameFinishedWithVictory';
    public const IsGameLost = 'IsGameFinishedWithDefeat';
    public const CardDeck = 'CardDeck';

    private function __construct()
    {
    }
}
