<?php

declare(strict_types=1);

namespace CardMultigame\Usecases\GameActions;

use CardMultigame\Entities\GameStates\GameState;
use CardMultigame\GameManagers\SelectedRules\PlayedGameRules;
use CardMultigame\Technical\NotImplementedException;
use CardMultigame\Usecases\InfluenceState\QueryGameState;

class DrawSingleCardAction implements IGameAction
{
    public function changeGameState(GameState $currentGameState, ?PlayedGameRules $gameRules, ?string $orderParams): void
    {
        QueryGameState::extractCardDeck($currentGameState)->drawRandomCard();
        if (QueryGameState::amountOfCardsLeft($currentGameState) === 0)
            $currentGameState['Guess'] = true;
    }

    public function shouldReactTo(string $item1): bool
    {
        throw new NotImplementedException();
    }
}
