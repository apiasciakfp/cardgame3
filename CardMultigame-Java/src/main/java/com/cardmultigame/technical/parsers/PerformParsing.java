package com.cardmultigame.technical.parsers;

import com.cardmultigame.technical.parsers.parsestrategies.IParseStrategy;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class PerformParsing {
    private final IParseStrategy parseStrategy;

    public PerformParsing(IParseStrategy parseStrategy) {
        this.parseStrategy = parseStrategy;
    }

    public List<ParsedOrder> executeOn(String orderString) {
        List<String> records = parseStrategy.splitIntoRecords(orderString);

        String singleFirstWord = "(\\b\\w+\\b){1}";

        List<ParsedOrder> actionsWithParams = new ArrayList<>();
        for (String record : records) {
            Pattern pattern = Pattern.compile(singleFirstWord, Pattern.MULTILINE);
            Matcher matcher = pattern.matcher(record);

            String actionSigil = "";
            if (matcher.find()) {
                actionSigil = matcher.group();
            }

            String paramsSigil = record.replace(actionSigil, "");

            actionsWithParams.add(new ParsedOrder(actionSigil.trim(), paramsSigil.trim()));
        }

        return actionsWithParams;
    }
}
