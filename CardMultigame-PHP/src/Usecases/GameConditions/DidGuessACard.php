<?php

declare(strict_types=1);

namespace CardMultigame\Usecases\GameConditions;

use CardMultigame\Entities\GameStates\GameState;
use CardMultigame\Usecases\InfluenceState\ModifyGameState;

class DidGuessACard implements IGameCondition
{
    public function checkAndUpdate(GameState $currentGameState): void
    {
        $result = $currentGameState['Guess'];
        if ($result !== null) {
            // C#: (result as bool?).Value, which throws when result is not a bool
            $isGameWon = (is_bool($result) ? $result : null) ?? throw new \LogicException('Nullable object must have a value.');
            if ($isGameWon) {
                ModifyGameState::declareGameToBeWon($currentGameState);
            }
        }
    }
}
