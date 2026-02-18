package com.cardmultigame.usecases.cardcomparison;

public class CreateCardComparisonStrategy {

    public ICardComparisonStrategy create(String selector) {
        if (selector.equals("strict")) return new StrictCardComparisonStrategy();
        if (selector.equals("colour")) return new ColourCardComparisonStrategy();
        if (selector.equals("blackred")) return new BlackRedColourOnlyComparisonStrategy();
        if (selector.equals("rank")) return new RankCardComparisonStrategy();
        return new AlwaysFailComparisonStrategy();
    }

    public ICardComparisonStrategy none() {
        return new AlwaysFailComparisonStrategy();
    }
}
