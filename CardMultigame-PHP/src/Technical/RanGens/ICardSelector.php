<?php

declare(strict_types=1);

namespace CardMultigame\Technical\RanGens;

use CardMultigame\Entities\Cards\Card;

interface ICardSelector
{
    /**
     * @param list<Card> $cards
     */
    public function drawCard(array $cards): Card;
}
