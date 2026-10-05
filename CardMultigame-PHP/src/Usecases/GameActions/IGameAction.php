<?php

declare(strict_types=1);

namespace CardMultigame\Usecases\GameActions;

use CardMultigame\Entities\GameStates\GameState;
use CardMultigame\GameManagers\SelectedRules\PlayedGameRules;

interface IGameAction
{
    public function shouldReactTo(string $item1): bool;

    public function changeGameState(GameState $currentGameState, ?PlayedGameRules $gameRules, ?string $orderParams): void;
}
