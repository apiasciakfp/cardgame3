<?php

declare(strict_types=1);

namespace CardMultigame\GameManagers\SelectedRules\CreationCommands;

use CardMultigame\GameManagers\GameManagerInternalsBuilder;
use CardMultigame\Technical\DotnetString;
use CardMultigame\Usecases\CardComparison\BlackRedColourOnlyComparisonStrategy;

class GameVariant implements ICreateGameRulesCommand
{
    private string $identifier = 'GameVariant';

    public function changeGameRuleset(GameManagerInternalsBuilder $builder, string $parameters): void
    {
        // First, the comparator
        $builder->setCardComparisonStrategy(new BlackRedColourOnlyComparisonStrategy());
    }

    public function shouldReactTo(string $outerCommandName): bool
    {
        return DotnetString::toLower($this->identifier) === DotnetString::toLower($outerCommandName);
    }
}
