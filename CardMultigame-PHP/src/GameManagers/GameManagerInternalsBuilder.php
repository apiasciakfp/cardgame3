<?php

declare(strict_types=1);

namespace CardMultigame\GameManagers;

use CardMultigame\Entities\Decks\CardDeck;
use CardMultigame\Entities\GameStates\CreateGameState;
use CardMultigame\Entities\GameStates\GameState;
use CardMultigame\Entities\GameStates\GameStateKeys;
use CardMultigame\GameManagers\SelectedRules\CreatePlayedGameRules;
use CardMultigame\GameManagers\SelectedRules\PlayedGameRules;
use CardMultigame\Usecases\CardComparison\ICardComparisonStrategy;
use CardMultigame\Usecases\GameActions\IGameAction;
use CardMultigame\Usecases\GameConditions\IGameCondition;

class GameManagerInternalsBuilder
{
    private ?string $gameName = null;
    private ?CardDeck $deck = null;
    /** @var list<IGameAction>|null */
    private ?array $actions = null;
    /** @var list<IGameCondition>|null */
    private ?array $victories = null;
    /** @var list<IGameCondition>|null */
    private ?array $gameStops = null;
    private ?GameState $initialGameState = null;

    //This one is specific to Guessing Game.
    private ?ICardComparisonStrategy $compareCards = null;

    public function constructRuleset(): PlayedGameRules
    {
        return (new CreatePlayedGameRules())->withModifications($this->gameName, $this->actions, $this->victories, $this->gameStops, $this->compareCards);
    }

    public function constructGameState(): GameState
    {
        return (new CreateGameState())->withModifications($this->initialGameState, $this->deck);
    }

    public function setName(?string $name): void { $this->gameName = $name; }
    public function setAvailableActions(?array $actions): void { $this->actions = $actions; }
    public function setVictoryConditions(?array $victories): void { $this->victories = $victories; }
    public function setGameStopConditions(?array $gameStops): void { $this->gameStops = $gameStops; }
    public function setDeck(?CardDeck $cardDeck): void { $this->deck = $cardDeck; }
    public function setInitialGameState(?GameState $gameState): void { $this->initialGameState = $gameState; }
    // C# NullReferenceException when no game was selected yet (wart 19); the typed ?GameState
    // property makes PHP throw too instead of auto-creating an array.
    public function setMaxTurns(int $maxTurns): void { $this->initialGameState[GameStateKeys::MaxTurns] = $maxTurns; }
    public function getCardDeck(): ?CardDeck { return $this->deck; }

    // Specific to Guessing Game. Should be more general, like with InternalState
    public function setCardComparisonStrategy(?ICardComparisonStrategy $selected): void { $this->compareCards = $selected; }
}
