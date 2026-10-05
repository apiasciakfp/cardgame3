<?php

declare(strict_types=1);

namespace CardMultigame\GameManagers\SelectedRules\CreationCommands;

use CardMultigame\GameManagers\GameManagerInternalsBuilder;
use CardMultigame\Technical\DotnetString;

class SetMaxTurns implements ICreateGameRulesCommand
{
    private string $identifier = 'SetMaxTurns';

    public function changeGameRuleset(GameManagerInternalsBuilder $builder, string $parameters): void
    {
        $wasSuccessful = DotnetString::tryParseInt($parameters, $maxTurns);
        if ($wasSuccessful) {
            $builder->setMaxTurns($maxTurns);
        }
    }

    public function shouldReactTo(string $outerCommandName): bool
    {
        return DotnetString::toLower($this->identifier) === DotnetString::toLower($outerCommandName);
    }
}
