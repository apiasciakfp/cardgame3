<?php

declare(strict_types=1);

namespace CardMultigame\GameManagers;

use CardMultigame\Entities\GameStates\GameState;
use CardMultigame\GameManagers\SelectedRules\PlayedGameRules;
use CardMultigame\Technical\Parsers\SelectedParser;
use CardMultigame\Usecases\InfluenceState\QueryGameState;

class GameManager
{
    private GameState $currentGameState;
    private PlayedGameRules $gameRules;

    public function __construct(GameState $initialState, PlayedGameRules $rules)
    {
        $this->currentGameState = $initialState;
        $this->gameRules = $rules;
    }

    public function executeOrders(string $orderString): void
    {
        $orders = (new SelectedParser())->properlyParse($orderString);
        foreach ($orders as $order) {
            if (QueryGameState::isGameFinished($this->currentGameState)) return;

            foreach ($this->gameRules->gameActions() as $gameAction) {
                if ($gameAction->shouldReactTo($order[0])) {
                    $gameAction->changeGameState($this->currentGameState, $this->gameRules, $order[1]);
                    $this->gameRules->checkVictoryConditions($this->currentGameState);
                    $this->gameRules->checkGameStopConditions($this->currentGameState);
                }
            }
        }
    }

    public function currentState(): GameState
    {
        return $this->currentGameState;
    }
}
