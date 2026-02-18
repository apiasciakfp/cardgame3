package com.cardmultigame.technical.rangens;

import com.cardmultigame.entities.cards.Card;
import java.util.List;

public class AlwaysLastSelector implements ICardSelector {
    @Override
    public Card drawCard(List<Card> cards) {
        return cards.get(cards.size() - 1);
    }
}
