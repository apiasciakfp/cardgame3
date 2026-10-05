<?php

declare(strict_types=1);

namespace CardMultigame\Technical\RanGens;

/**
 * Non-mirror helper: the parts of .NET System.Random this app relies on.
 *
 * - A seeded generator object (C# `new Random(seed)`): same seed, same sequence.
 * - Next(minValue, maxValue) with an EXCLUSIVE upper bound; minValue === maxValue returns minValue;
 *   maxValue < minValue throws (.NET ArgumentOutOfRangeException, an ArgumentException).
 *
 * Only the semantics are mirrored, not .NET's generator algorithm.
 */
class DotnetRandom
{
    private \Random\Randomizer $randomizer;

    public function __construct(int $seed)
    {
        $this->randomizer = new \Random\Randomizer(new \Random\Engine\Mt19937($seed));
    }

    public function next(int $minValue, int $maxValue): int
    {
        if ($maxValue < $minValue) {
            throw new \InvalidArgumentException("'minValue' cannot be greater than maxValue. (Parameter 'minValue')");
        }

        if ($minValue === $maxValue) {
            return $minValue;
        }

        return $this->randomizer->getInt($minValue, $maxValue - 1);
    }
}
