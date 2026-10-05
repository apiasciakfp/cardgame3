<?php

declare(strict_types=1);

namespace CardMultigame\Usecases\GameActions;

use CardMultigame\Entities\Cards\CreateCards;
use CardMultigame\Entities\GameStates\GameState;
use CardMultigame\GameManagers\SelectedRules\PlayedGameRules;
use CardMultigame\Technical\DotnetString;
use CardMultigame\Usecases\InfluenceState\ModifyGameState;
use CardMultigame\Usecases\InfluenceState\QueryGameState;

class GuessCardAction implements IGameAction
{
    private string $identifier = 'Guess';

    public function changeGameState(GameState $currentGameState, ?PlayedGameRules $rules, ?string $orderParams): void
    {
        $candidate = (new CreateCards())->createSingle($orderParams);
        $deck = QueryGameState::extractCardDeck($currentGameState);
        $actuallyDrawnCard = $deck->drawRandomCard();
        $comparator = $rules->cardComparator();
        $areTheSame = $comparator->areTheSame($candidate, $actuallyDrawnCard);

        if ($areTheSame) $currentGameState[$this->identifier] = true;
        else $currentGameState[$this->identifier] = false;

        ModifyGameState::addTurn($currentGameState);
    }

    public function shouldReactTo(string $orderName): bool
    {
        return DotnetString::toLower($this->identifier) === DotnetString::toLower($orderName);
    }
}
