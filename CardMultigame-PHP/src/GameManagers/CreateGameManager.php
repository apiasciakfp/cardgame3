<?php

declare(strict_types=1);

namespace CardMultigame\GameManagers;

use CardMultigame\Entities\GameStates\CreateGameState;
use CardMultigame\GameManagers\SelectedRules\CreateGameStructure;
use CardMultigame\GameManagers\SelectedRules\CreatePlayedGameRules;
use CardMultigame\Technical\Parsers\SelectedParser;

class CreateGameManager
{
    public function defaultsWithOrders(string $orderString): GameManager
    {
        $orders = (new SelectedParser())->properlyParse($orderString);
        $builder = (new CreateGameStructure())->buildRulesAndInitialState($orders);
        $rules = $builder->constructRuleset();
        $initialState = $builder->constructGameState();
        return new GameManager($initialState, $rules);
    }

    public function empty(): GameManager
    {
        $initialState = (new CreateGameState())->default();
        $rules = (new CreatePlayedGameRules())->empty();
        return new GameManager($initialState, $rules);
    }
}
