<?php

declare(strict_types=1);

namespace CardMultigame\GameManagers\SelectedRules;

use CardMultigame\Entities\GameStates\GameState;
use CardMultigame\Usecases\CardComparison\ICardComparisonStrategy;
use CardMultigame\Usecases\GameActions\IGameAction;
use CardMultigame\Usecases\GameConditions\IGameCondition;

class PlayedGameRules
{
    private ?string $gameName;
    /** @var list<IGameAction>|null */
    private ?array $actions;
    /** @var list<IGameCondition>|null */
    private ?array $victoryConditions;
    /** @var list<IGameCondition>|null */
    private ?array $gameStopConditions;
    private ?ICardComparisonStrategy $cardComparator;

    public function __construct(?string $gameName, ?array $actions, ?array $victories,
        ?array $gameStops, ?ICardComparisonStrategy $compareCards)
    {
        $this->gameName = $gameName;
        $this->actions = $actions;
        $this->victoryConditions = $victories;
        $this->gameStopConditions = $gameStops;
        $this->cardComparator = $compareCards;
    }

    public function cardComparator(): ?ICardComparisonStrategy
    {
        return $this->cardComparator;
    }

    // Usually those three would remain private.
    // But tests for patterns kind of need it.
    // (Returned by reference: the internal lists are exposed, as in C#.)
    public function &gameActions(): ?array { return $this->actions; }
    public function &victoryConditions(): ?array { return $this->victoryConditions; }
    public function &gameStopConditions(): ?array { return $this->gameStopConditions; }
    public function gameName(): ?string { return $this->gameName; }

    public function checkVictoryConditions(GameState $currentGameState): void
    {
        foreach ($this->victoryConditions as $victory) {
            $victory->checkAndUpdate($currentGameState);
        }
    }

    public function checkGameStopConditions(GameState $currentGameState): void
    {
        foreach ($this->gameStopConditions as $stop) {
            $stop->checkAndUpdate($currentGameState);
        }
    }
}
