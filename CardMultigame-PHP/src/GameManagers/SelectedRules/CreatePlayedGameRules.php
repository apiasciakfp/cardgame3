<?php

declare(strict_types=1);

namespace CardMultigame\GameManagers\SelectedRules;

use CardMultigame\Usecases\CardComparison\CreateCardComparisonStrategy;
use CardMultigame\Usecases\CardComparison\ICardComparisonStrategy;
use CardMultigame\Usecases\GameActions\IGameAction;
use CardMultigame\Usecases\GameConditions\IGameCondition;

class CreatePlayedGameRules
{
    private string $defaultGameName = 'No game selected';
    /** @var list<IGameAction> */
    private array $defaultActions = [];
    /** @var list<IGameCondition> */
    private array $defaultVictories = [];
    /** @var list<IGameCondition> */
    private array $defaultGameStops = [];
    private ICardComparisonStrategy $defaultCardComparators;

    public function __construct()
    {
        $this->defaultCardComparators = (new CreateCardComparisonStrategy())->none();
    }

    public function empty(): PlayedGameRules
    {
        return new PlayedGameRules($this->defaultGameName, $this->defaultActions, $this->defaultVictories, $this->defaultGameStops, $this->defaultCardComparators);
    }

    public function withModifications(?string $gameName, ?array $actions, ?array $victories,
        ?array $gameStops, ?ICardComparisonStrategy $compareCards): PlayedGameRules
    {
        $selectedName = $this->defaultGameName;
        $selectedActions = $this->defaultActions;
        $selectedVictories = $this->defaultVictories;
        $selectedGameStops = $this->defaultGameStops;
        $selectedCardComparators = $this->defaultCardComparators;

        if ($gameName !== null)
            $selectedName = $gameName;
        if ($actions !== null)
            $selectedActions = $actions;
        if ($victories !== null)
            $selectedVictories = $victories;
        if ($gameStops !== null)
            $selectedGameStops = $gameStops;
        if ($compareCards !== null)
            $selectedCardComparators = $compareCards;

        return new PlayedGameRules($selectedName, $selectedActions, $selectedVictories, $selectedGameStops, $selectedCardComparators);
    }
}
