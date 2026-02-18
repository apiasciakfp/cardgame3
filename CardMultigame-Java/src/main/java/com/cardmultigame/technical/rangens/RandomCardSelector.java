package com.cardmultigame.technical.rangens;

import com.cardmultigame.entities.cards.Card;
import java.util.List;
import java.util.Random;

public class RandomCardSelector implements ICardSelector {
    // Faithful to C# original: seeded with millisecond component only
    private final Random random = new Random(System.currentTimeMillis() % 1000);

    @Override
    public Card drawCard(List<Card> cards) {
        // BUG (faithful to C# original): cards.size() - 1 excludes the last card.
        // C# Random.Next(0, count-1) never picks index count-1 when count > 1.
        // Java Random.nextInt is also exclusive, so nextInt(size-1) has same behavior.
        // Edge case: when size == 1, C# Next(0,0) returns 0; Java nextInt(0) would throw.
        if (cards.size() == 1) {
            return cards.get(0);
        }
        int index = random.nextInt(cards.size() - 1);
        return cards.get(index);
    }
}
