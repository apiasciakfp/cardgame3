package com.cardmultigame.usecases.cardcomparison;

import com.cardmultigame.entities.cards.Card;
import java.util.Map;

public class BlackRedColourOnlyComparisonStrategy implements ICardComparisonStrategy {
    @Override
    public boolean areTheSame(Card card1, Card card2) {
        Map<String, String> colourMap = Map.of(
            "H", "red",
            "D", "red",
            "C", "black",
            "S", "black"
        );

        String card1Colour = colourMap.get(card1.colour());
        String card2Colour = colourMap.get(card2.colour());

        return card1Colour.equals(card2Colour);
    }
}
