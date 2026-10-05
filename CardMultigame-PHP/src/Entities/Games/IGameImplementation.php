<?php

declare(strict_types=1);

namespace CardMultigame\Entities\Games;

use CardMultigame\Entities\Decks\CardDeck;
use CardMultigame\Entities\GameStates\GameState;
use CardMultigame\Usecases\CardComparison\ICardComparisonStrategy;
use CardMultigame\Usecases\GameActions\IGameAction;
use CardMultigame\Usecases\GameConditions\IGameCondition;

interface IGameImplementation
{
    public function title(): string;

    public function cardDeck(): CardDeck;

    /** @return list<IGameAction> */
    public function availableActions(): array;

    /** @return list<IGameCondition> */
    public function victoryConditions(): array;

    /** @return list<IGameCondition> */
    public function gameStopConditions(): array;

    public function initialGameState(): GameState;

    public function cardComparisonStrategy(): ICardComparisonStrategy;
}
