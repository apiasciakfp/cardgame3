package com.cardmultigame.usecases.cardcomparison;

import com.cardmultigame.entities.cards.Card;

public class AlwaysFailComparisonStrategy implements ICardComparisonStrategy {
    @Override
    public boolean areTheSame(Card card1, Card card2) {
        return false;
    }
}
