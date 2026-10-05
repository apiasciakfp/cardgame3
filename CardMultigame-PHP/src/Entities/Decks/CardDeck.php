<?php

declare(strict_types=1);

namespace CardMultigame\Entities\Decks;

use CardMultigame\Entities\Cards\Card;
use CardMultigame\Technical\RanGens\ICardSelector;

class CardDeck
{
    private ICardSelector $selector;
    /** @var list<Card> */
    private array $cards = [];

    /**
     * @param list<Card> $cards
     */
    public function __construct(ICardSelector $selector, array $cards)
    {
        $this->selector = $selector;
        $this->cards = $cards;
    }

    /**
     * Returns the internal list by reference, as C# does (bind with =& to see the leak).
     *
     * @return list<Card>
     */
    public function &allCards(): array { return $this->cards; }
    public function cardsLeft(): int { return count($this->cards); }

    public function drawRandomCard(): Card
    {
        $drawn = $this->selector->drawCard($this->cards);
        $this->removeCard($drawn);

        return $drawn;
    }

    public function drawLastAddedCard(): Card
    {
        $drawn = $this->cards[count($this->cards) - 1];
        $this->removeCard($drawn);

        return $drawn;
    }

    public function addASingleCard(Card $card): void
    {
        $this->cards[] = $card;
    }

    public function __toString(): string
    {
        $cardFaces = array_reduce($this->cards, static fn (string $acc, Card $prm): string => $acc . '||' . $prm, '');
        return "Deck: {$cardFaces}";
    }

    /**
     * C# List.Remove: first element that is the SAME INSTANCE (Card has no Equals override),
     * indices stay dense. Strict array_search compares objects by identity.
     */
    private function removeCard(Card $card): void
    {
        $index = array_search($card, $this->cards, true);
        if ($index !== false) {
            array_splice($this->cards, $index, 1);
        }
    }
}
