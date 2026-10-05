<?php

declare(strict_types=1);

namespace CardMultigame\Technical\RanGens;

use CardMultigame\Entities\Cards\Card;

class AlwaysLastSelector implements ICardSelector
{
    public function drawCard(array $cards): Card
    {
        return $cards[count($cards) - 1];
    }
}
