<?php

declare(strict_types=1);

namespace CardMultigame\GameManagers\SelectedRules\CreationCommands;

use CardMultigame\GameManagers\GameManagerInternalsBuilder;

interface ICreateGameRulesCommand
{
    public function shouldReactTo(string $outerCommandName): bool;

    public function changeGameRuleset(GameManagerInternalsBuilder $builder, string $parameters): void;
}
