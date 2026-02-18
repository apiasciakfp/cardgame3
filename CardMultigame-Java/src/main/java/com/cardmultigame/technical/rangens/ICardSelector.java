package com.cardmultigame.technical.rangens;

import com.cardmultigame.entities.cards.Card;
import java.util.List;

public interface ICardSelector {
    Card drawCard(List<Card> cards);
}
