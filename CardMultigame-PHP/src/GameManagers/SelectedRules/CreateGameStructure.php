<?php

declare(strict_types=1);

namespace CardMultigame\GameManagers\SelectedRules;

use CardMultigame\GameManagers\GameManagerInternalsBuilder;
use CardMultigame\GameManagers\SelectedRules\CreationCommands\GameVariant;
use CardMultigame\GameManagers\SelectedRules\CreationCommands\ICreateGameRulesCommand;
use CardMultigame\GameManagers\SelectedRules\CreationCommands\SelectGame;
use CardMultigame\GameManagers\SelectedRules\CreationCommands\SetDeck;
use CardMultigame\GameManagers\SelectedRules\CreationCommands\SetMaxTurns;

class CreateGameStructure
{
    /** @var list<ICreateGameRulesCommand> */
    private array $commands;

    public function __construct()
    {
        $this->commands = $this->registerAvailableCreationCommands();
    }

    /**
     * @param list<array{0: string, 1: string}> $orders
     */
    public function buildRulesAndInitialState(array $orders): GameManagerInternalsBuilder
    {
        $builder = new GameManagerInternalsBuilder();
        foreach ($orders as $order) {
            foreach ($this->commands as $orderUser) {
                if ($orderUser->shouldReactTo($order[0])) {
                    $orderUser->changeGameRuleset($builder, $order[1]);
                }
            }
        }

        return $builder;
    }

    /**
     * @return list<ICreateGameRulesCommand>
     */
    private function registerAvailableCreationCommands(): array
    {
        return [new SelectGame(), new SetDeck(), new SetMaxTurns(),
            new GameVariant()];
    }
}
