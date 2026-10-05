<?php

declare(strict_types=1);

namespace CardMultigame\Entities\Decks;

use CardMultigame\Entities\Cards\CreateCards;
use CardMultigame\Technical\RanGens\ICardSelector;
use CardMultigame\Technical\RanGens\RandomCardSelector;

class CreateCardDeck
{
    private ICardSelector $selectedCardSelector;

    public function __construct()
    {
        $this->selectedCardSelector = new RandomCardSelector();
    }

    public function fromGivenCards(string $cardsInDeck): CardDeck
    {
        $cards = (new CreateCards())->createCollection($cardsInDeck);
        return new CardDeck($this->selectedCardSelector, $cards);
    }

    public function simple9ToAWith4Colours(): CardDeck
    {
        $ranks = ['9', '10', 'J', 'Q', 'K', 'A'];
        $colours = ['S', 'H', 'D', 'C'];

        $cards = [];
        foreach ($ranks as $rank) {
            foreach ($colours as $colour) {
                $cardPrototype = $rank . $colour;
                $card = (new CreateCards())->createSingle($cardPrototype);
                $cards[] = $card;
            }
        }

        return new CardDeck($this->selectedCardSelector, $cards);
    }

    public function simple2ToAWith4Colours(): CardDeck
    {
        $ranks = ['2', '3', '4', '5', '6', '7', '8',
            '9', '10', 'J', 'Q', 'K', 'A'];
        $colours = ['S', 'H', 'D', 'C'];

        $cards = [];
        foreach ($ranks as $rank) {
            foreach ($colours as $colour) {
                $cardPrototype = $rank . $colour;
                $card = (new CreateCards())->createSingle($cardPrototype);
                $cards[] = $card;
            }
        }

        return new CardDeck($this->selectedCardSelector, $cards);
    }

    public function empty(): CardDeck
    {
        return new CardDeck($this->selectedCardSelector, []);
    }

    /**
     * This is a setter method to change the default random generator
     */
    public function setCardSelector(ICardSelector $selector): void
    {
        $this->selectedCardSelector = $selector;
    }
}
