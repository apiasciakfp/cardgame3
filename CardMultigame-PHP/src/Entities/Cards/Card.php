<?php

declare(strict_types=1);

namespace CardMultigame\Entities\Cards;

class Card
{
    private string $rank;
    private string $colour;

    public function __construct(string $rank, string $colour)
    {
        $this->rank = $rank;
        $this->colour = $colour;
    }

    public function rank(): string
    {
        return $this->rank;
    }

    public function colour(): string
    {
        return $this->colour;
    }

    public function __toString(): string
    {
        return "r: {$this->rank()} c: {$this->colour()}";
    }
}
