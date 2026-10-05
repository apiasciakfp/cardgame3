<?php

declare(strict_types=1);

namespace CardMultigame\Usecases\CardComparison;

use CardMultigame\Entities\Cards\Card;

class StrictCardComparisonStrategy implements ICardComparisonStrategy
{
    public function areTheSame(?Card $card1, ?Card $card2): bool
    {
        if (($card1->rank() === $card2->rank()) && ($card1->colour() === $card2->colour())) {
            return true;
        } else {
            return false;
        }
    }
}
