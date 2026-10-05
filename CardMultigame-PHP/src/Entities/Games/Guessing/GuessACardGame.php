<?php

declare(strict_types=1);

namespace CardMultigame\Entities\Games\Guessing;

use CardMultigame\Entities\Decks\CardDeck;
use CardMultigame\Entities\Decks\CreateCardDeck;
use CardMultigame\Entities\Games\IGameImplementation;
use CardMultigame\Entities\GameStates\GameState;
use CardMultigame\Entities\GameStates\GameStateKeys;
use CardMultigame\Usecases\CardComparison\ICardComparisonStrategy;
use CardMultigame\Usecases\CardComparison\StrictCardComparisonStrategy;
use CardMultigame\Usecases\GameActions\GuessCardAction;
use CardMultigame\Usecases\GameConditions\DidGuessACard;
use CardMultigame\Usecases\GameConditions\DidTurnsExpire;

class GuessACardGame implements IGameImplementation
{
    public function cardDeck(): CardDeck
    {
        return (new CreateCardDeck())->simple9ToAWith4Colours();
    }

    public function availableActions(): array
    {
        return [new GuessCardAction()];
    }

    public function gameStopConditions(): array
    {
        return [new DidTurnsExpire()];
    }

    public function victoryConditions(): array
    {
        return [new DidGuessACard()];
    }

    public function initialGameState(): GameState
    {
        return new GameState([
            GameStateKeys::MaxTurns => 5,
        ]);
    }

    public function title(): string
    {
        return 'Guess a Card!';
    }

    public function cardComparisonStrategy(): ICardComparisonStrategy
    {
        return new StrictCardComparisonStrategy();
    }
}
