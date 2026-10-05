<?php

declare(strict_types=1);

namespace CardMultigame\Usecases\GameConditions;

use CardMultigame\Entities\GameStates\GameState;

interface IGameCondition
{
    public function checkAndUpdate(GameState $currentGameState): void;
}
