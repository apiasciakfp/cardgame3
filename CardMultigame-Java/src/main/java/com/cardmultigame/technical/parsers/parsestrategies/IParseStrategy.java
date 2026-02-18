package com.cardmultigame.technical.parsers.parsestrategies;

import java.util.List;

public interface IParseStrategy {
    String separator();
    List<String> splitIntoRecords(String orderString);
}
