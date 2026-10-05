<?php

declare(strict_types=1);

namespace CardMultigame\Technical\RanGens;

use CardMultigame\Entities\Cards\Card;

class RandomCardSelector implements ICardSelector
{
    private DotnetRandom $random;

    public function __construct()
    {
        // C#: new Random(DateTime.Now.Millisecond): the millisecond component (0..999) is the seed.
        $this->random = new DotnetRandom((int) (new \DateTimeImmutable())->format('v'));
    }

    public function drawCard(array $cards): Card
    {
        $index = $this->random->next(0, count($cards) - 1);
        $drawn = $cards[$index];
        return $drawn;
    }
}
