<?php

declare(strict_types=1);

namespace CardMultigame\GameManagers\SelectedRules\CreationCommands;

use CardMultigame\Entities\Games\Guessing\GuessACardGame;
use CardMultigame\Entities\Games\IGameImplementation;
use CardMultigame\GameManagers\GameManagerInternalsBuilder;
use CardMultigame\Technical\DotnetString;

class SelectGame implements ICreateGameRulesCommand
{
    private string $identifier = 'Play';

    public function changeGameRuleset(GameManagerInternalsBuilder $builder, string $parameters): void
    {
        $gameImpl = self::selectGameImplementation($parameters);
        $builder->setName($gameImpl->title());
        $builder->setDeck($gameImpl->cardDeck());
        $builder->setAvailableActions($gameImpl->availableActions());
        $builder->setVictoryConditions($gameImpl->victoryConditions());
        $builder->setGameStopConditions($gameImpl->gameStopConditions());
        $builder->setInitialGameState($gameImpl->initialGameState());
        $builder->setCardComparisonStrategy($gameImpl->cardComparisonStrategy());
    }

    public function shouldReactTo(string $outerCommandName): bool
    {
        return DotnetString::toLower($this->identifier) === DotnetString::toLower($outerCommandName);
    }

    private static function selectGameImplementation(string $parameters): IGameImplementation
    {
        $gameImpl = null;
        if (DotnetString::toLower($parameters) === DotnetString::toLower('GuessACard')) {
            $gameImpl = new GuessACardGame();
        }

        if ($gameImpl === null) throw new \InvalidArgumentException('Either the game is not registered in factory or game identifier has a typo. Got: ' . $parameters);
        return $gameImpl;
    }
}
