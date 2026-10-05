<?php

declare(strict_types=1);

namespace CardMultigame\GameManagers\SelectedRules\CreationCommands;

use CardMultigame\Entities\Decks\CreateCardDeck;
use CardMultigame\GameManagers\GameManagerInternalsBuilder;
use CardMultigame\Technical\DotnetString;

class SetDeck implements ICreateGameRulesCommand
{
    private string $identifier = 'SetDeck';

    public function changeGameRuleset(GameManagerInternalsBuilder $builder, string $parameters): void
    {
        $deck = (new CreateCardDeck())->fromGivenCards($parameters);
        $builder->setDeck($deck);
    }

    public function shouldReactTo(string $outerCommandName): bool
    {
        return DotnetString::toLower($this->identifier) === DotnetString::toLower($outerCommandName);
    }
}
