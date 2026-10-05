<?php

declare(strict_types=1);

namespace CardMultigame\Technical\RanGens;

use CardMultigame\Entities\Cards\Card;

class AlwaysFirstSelector implements ICardSelector
{
    public function drawCard(array $cards): Card
    {
        return $cards[0];
    }
}
