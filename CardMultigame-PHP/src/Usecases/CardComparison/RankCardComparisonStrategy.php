<?php

declare(strict_types=1);

namespace CardMultigame\Usecases\CardComparison;

use CardMultigame\Entities\Cards\Card;

class RankCardComparisonStrategy implements ICardComparisonStrategy
{
    public function areTheSame(?Card $card1, ?Card $card2): bool
    {
        if ($card1->rank() === $card2->rank()) {
            return true;
        } else {
            return false;
        }
    }
}
