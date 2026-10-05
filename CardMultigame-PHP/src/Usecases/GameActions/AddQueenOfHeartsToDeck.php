<?php

declare(strict_types=1);

namespace CardMultigame\Usecases\GameActions;

use CardMultigame\Entities\Cards\Card;
use CardMultigame\Entities\GameStates\GameState;
use CardMultigame\GameManagers\SelectedRules\PlayedGameRules;
use CardMultigame\Technical\NotImplementedException;
use CardMultigame\Usecases\InfluenceState\QueryGameState;

class AddQueenOfHeartsToDeck implements IGameAction
{
    public function changeGameState(GameState $currentGameState, ?PlayedGameRules $gameRules, ?string $orderParams): void
    {
        $deck = QueryGameState::extractCardDeck($currentGameState);
        $deck->addASingleCard(new Card('Q', 'H'));
    }

    public function shouldReactTo(string $item1): bool
    {
        throw new NotImplementedException();
    }
}
