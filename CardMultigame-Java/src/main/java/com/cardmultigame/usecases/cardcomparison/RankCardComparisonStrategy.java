package com.cardmultigame.usecases.cardcomparison;

import com.cardmultigame.entities.cards.Card;

public class RankCardComparisonStrategy implements ICardComparisonStrategy {
    @Override
    public boolean areTheSame(Card card1, Card card2) {
        return card1.rank().equals(card2.rank());
    }
}
