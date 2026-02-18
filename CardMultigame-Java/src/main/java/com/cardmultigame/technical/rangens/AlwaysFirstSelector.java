package com.cardmultigame.technical.rangens;

import com.cardmultigame.entities.cards.Card;
import java.util.List;

public class AlwaysFirstSelector implements ICardSelector {
    @Override
    public Card drawCard(List<Card> cards) {
        return cards.get(0);
    }
}
