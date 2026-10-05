<?php

declare(strict_types=1);

namespace CardMultigame\Interface;

use CardMultigame\GameManagers\CreateGameManager;
use CardMultigame\GameManagers\GameManager;
use CardMultigame\Technical\DotnetString;

class UiLogicDispatcher
{
    private GameManager $gameManager;

    public function __construct()
    {
        $this->gameManager = (new CreateGameManager())->empty();
    }

    public function doStuff(string $orders): void
    {
        $this->gameManager->executeOrders($orders);
    }

    public function setupGame(string $orders): void
    {
        $this->gameManager = (new CreateGameManager())->defaultsWithOrders($orders);
    }

    public function displayCurrentState(): string
    {
        $currentState = $this->gameManager->currentState();

        // C#: string.Join(";" + Environment.NewLine, currentState), where each entry prints as
        // KeyValuePair.ToString(): "[key, value]".
        $entries = [];
        foreach ($currentState as $key => $value) {
            $entries[] = '[' . $key . ', ' . DotnetString::toString($value) . ']';
        }

        return implode(';' . PHP_EOL, $entries);
    }
}
