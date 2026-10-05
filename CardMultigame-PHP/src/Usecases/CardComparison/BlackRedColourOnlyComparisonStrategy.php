<?php

declare(strict_types=1);

namespace CardMultigame\Usecases\CardComparison;

use CardMultigame\Entities\Cards\Card;

class BlackRedColourOnlyComparisonStrategy implements ICardComparisonStrategy
{
    public function areTheSame(?Card $card1, ?Card $card2): bool
    {
        $colourMap = [
            'H' => 'red',
            'D' => 'red',
            'C' => 'black',
            'S' => 'black',
        ];
        // C# Dictionary indexer throws KeyNotFoundException on a missing key ("Damaged");
        // the installed PhpErrorsAsExceptions handler turns PHP's warning into the same crash.
        $card1Colour = $colourMap[$card1->colour()];
        $card2Colour = $colourMap[$card2->colour()];
        if ($card1Colour === $card2Colour) {
            return true;
        } else {
            return false;
        }
    }
}
