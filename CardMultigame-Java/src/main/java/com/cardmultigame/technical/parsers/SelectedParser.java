package com.cardmultigame.technical.parsers;

import com.cardmultigame.technical.parsers.parsestrategies.CommaParseStrategy;
import com.cardmultigame.technical.parsers.parsestrategies.DashParseStrategy;
import com.cardmultigame.technical.parsers.parsestrategies.IParseStrategy;
import com.cardmultigame.technical.parsers.parsestrategies.SemicolonParseStrategy;
import java.util.List;

public class SelectedParser {
    private final List<IParseStrategy> parseStrategies;

    public SelectedParser() {
        parseStrategies = registerPossibleStrategies();
    }

    public List<ParsedOrder> properlyParse(String orderString) {
        IParseStrategy selectedStrategy = selectAppropriateStrategy(orderString);

        if (selectedStrategy == null) {
            throw new IllegalArgumentException(
                "Order string is wrong or appropriate parsing Strategy is not registered");
        }

        return new PerformParsing(selectedStrategy).executeOn(orderString);
    }

    private IParseStrategy selectAppropriateStrategy(String orderString) {
        int lastPosition = Integer.MAX_VALUE;
        IParseStrategy selectedStrategy = null;

        for (IParseStrategy strategy : parseStrategies) {
            String potential = strategy.separator();
            int currentPosition = orderString.indexOf(potential);

            // BUG (faithful to C# original): > 0 rejects separator at position 0.
            // Should be >= 0 to accept separators at the start of the string.
            if (currentPosition > 0 && currentPosition < lastPosition) {
                selectedStrategy = strategy;
                lastPosition = currentPosition;
            }
        }

        return selectedStrategy;
    }

    private List<IParseStrategy> registerPossibleStrategies() {
        return List.of(
            new CommaParseStrategy(),
            new SemicolonParseStrategy(),
            new DashParseStrategy()
        );
    }
}
