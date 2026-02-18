package com.cardmultigame.usecases.cardcomparison;

import com.cardmultigame.entities.cards.Card;

public class ColourCardComparisonStrategy implements ICardComparisonStrategy {
    @Override
    public boolean areTheSame(Card card1, Card card2) {
        return card1.colour().equals(card2.colour());
    }
}
