<?php

declare(strict_types=1);

namespace CardMultigame\Usecases\InfluenceState;

use CardMultigame\Entities\GameStates\GameState;
use CardMultigame\Entities\GameStates\GameStateKeys;

final class ModifyGameState
{
    public static function addTurn(GameState $currentGameState): void
    {
        $currentTurn = is_int($currentGameState[GameStateKeys::CurrentTurn]) ? $currentGameState[GameStateKeys::CurrentTurn] : null; // C#: as int?
        $currentGameState[GameStateKeys::CurrentTurn] = $currentTurn === null ? null : $currentTurn + 1; // C#: (null + 1) is null
    }

    public static function declareGameToBeLost(GameState $currentGameState): void
    {
        $currentGameState[GameStateKeys::IsGameLost] = true;
    }

    public static function declareGameToBeWon(GameState $currentGameState): void
    {
        $currentGameState[GameStateKeys::IsGameWon] = true;
    }

    private function __construct()
    {
    }
}
