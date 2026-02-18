package com.cardmultigame.usecases.cardcomparison;

import com.cardmultigame.entities.cards.Card;

public interface ICardComparisonStrategy {
    boolean areTheSame(Card card1, Card card2);
}
