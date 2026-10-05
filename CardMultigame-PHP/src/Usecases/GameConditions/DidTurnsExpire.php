<?php

declare(strict_types=1);

namespace CardMultigame\Usecases\GameConditions;

use CardMultigame\Entities\GameStates\GameState;
use CardMultigame\Usecases\InfluenceState\ModifyGameState;
use CardMultigame\Usecases\InfluenceState\QueryGameState;

class DidTurnsExpire implements IGameCondition
{
    public function checkAndUpdate(GameState $currentGameState): void
    {
        $currentTurn = QueryGameState::currentTurn($currentGameState);
        $maxTurns = QueryGameState::maximumTurns($currentGameState);
        if ($currentTurn >= $maxTurns) {
            ModifyGameState::declareGameToBeLost($currentGameState);
        }
    }
}
