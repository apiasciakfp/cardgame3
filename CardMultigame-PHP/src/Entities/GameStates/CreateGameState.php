<?php

declare(strict_types=1);

namespace CardMultigame\Entities\GameStates;

use CardMultigame\Entities\Decks\CardDeck;
use CardMultigame\Entities\Decks\CreateCardDeck;

class CreateGameState
{
    public function withModifications(?GameState $stateModifier = null, ?CardDeck $deck = null): GameState
    {
        $deck2 = self::sanitizeDeck($deck);
        $stateModifier2 = $this->sanitizeState($stateModifier);

        $constructedState = $this->default();
        foreach ($stateModifier2 as $key => $value) {
            $constructedState[$key] = $value;
        }

        $constructedState[GameStateKeys::CardDeck] = $deck2;
        return $constructedState;
    }

    public function defaultsPlusDeck(?CardDeck $deck): GameState
    {
        $constructedState = $this->default();
        $constructedState[GameStateKeys::CardDeck] = $deck;
        return $constructedState;
    }

    public function defaultsWithFullDeck(): GameState
    {
        $constructedState = $this->default();
        $constructedState[GameStateKeys::CardDeck] = (new CreateCardDeck())->simple2ToAWith4Colours();
        return $constructedState;
    }

    public function default(): GameState
    {
        return new GameState([
            GameStateKeys::CardDeck => (new CreateCardDeck())->empty(),
            GameStateKeys::CurrentTurn => 0,
            GameStateKeys::MaxTurns => 0,
            GameStateKeys::IsGameLost => false,
            GameStateKeys::IsGameWon => false,
        ]);
    }

    private function sanitizeState(?GameState $stateModifier): GameState
    {
        if ($stateModifier === null) {
            return new GameState();
        } else {
            return $stateModifier;
        }
    }

    private static function sanitizeDeck(?CardDeck $deck): CardDeck
    {
        if ($deck === null) {
            return (new CreateCardDeck())->empty();
        } else {
            return $deck;
        }
    }
}
