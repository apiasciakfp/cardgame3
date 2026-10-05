<?php

declare(strict_types=1);

namespace CardMultigame\Usecases\CardComparison;

class CreateCardComparisonStrategy
{
    public function create(?string $selector): ICardComparisonStrategy
    {
        if ($selector === 'strict') return new StrictCardComparisonStrategy();
        if ($selector === 'colour') return new ColourCardComparisonStrategy();
        if ($selector === 'blackred') return new BlackRedColourOnlyComparisonStrategy();
        if ($selector === 'rank') return new RankCardComparisonStrategy();
        else return new AlwaysFailComparisonStrategy();
    }

    public function none(): ICardComparisonStrategy
    {
        return new AlwaysFailComparisonStrategy();
    }
}
