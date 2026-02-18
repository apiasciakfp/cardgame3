package com.cardmultigame.technical.parsers.parsestrategies;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;

public class DashParseStrategy implements IParseStrategy {
    private final String separator = "-";

    @Override
    public String separator() {
        return separator;
    }

    @Override
    public List<String> splitIntoRecords(String orderString) {
        String[] records = orderString.split(Pattern.quote(separator), -1);

        List<String> sanitizedRecords = new ArrayList<>();
        for (String record : records) {
            if (record != null && !record.isEmpty()) {
                // BUG (faithful to C# original): trims into 'sanitized' but checks/adds 'record' (untrimmed).
                String sanitized = record.trim();
                if (record != null && !record.isEmpty()) {
                    sanitizedRecords.add(record);
                }
            }
        }
        return sanitizedRecords;
    }
}
