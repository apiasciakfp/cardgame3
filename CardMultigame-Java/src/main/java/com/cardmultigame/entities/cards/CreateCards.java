package com.cardmultigame.entities.cards;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class CreateCards {

    public List<Card> createCollection(String cardStrings) {
        String cardPrototypePattern = "((\\b\\w{2,3}\\b)+)";
        Pattern pattern = Pattern.compile(cardPrototypePattern, Pattern.MULTILINE);
        Matcher matcher = pattern.matcher(cardStrings);

        List<Card> cards = new ArrayList<>();
        while (matcher.find()) {
            String prototype = matcher.group();
            if (isValidCardPrototype(prototype)) {
                cards.add(createSingle(prototype));
            }
        }
        return cards;
    }

    public Card createSingle(String prototype) {
        if (!isValidCardPrototype(prototype)) {
            return damagedCard();
        }
        String rank = extractRank(prototype);
        String colour = extractColour(prototype);
        return new Card(rank, colour);
    }

    private String extractColour(String prototype) {
        String colourSign = prototype.substring(prototype.length() - 1);
        if (colourSign.toUpperCase().equals("S")) return "S";
        if (colourSign.toUpperCase().equals("H")) return "H";
        if (colourSign.toUpperCase().equals("D")) return "D";
        if (colourSign.toUpperCase().equals("C")) return "C";
        throw new IllegalArgumentException("Colour extraction failed. Instead of SHDC we got: " + colourSign);
    }

    private String extractRank(String prototype) {
        return prototype.substring(0, prototype.length() - 1);
    }

    private Card damagedCard() {
        return new Card("Damaged", "Damaged");
    }

    private boolean isValidCardPrototype(String prototype) {
        String exactCardPrototypePattern = "\\b(10[shdcSHDC]|[2-9jqkaJQKA][shdcSHDC])\\b";
        Pattern pattern = Pattern.compile(exactCardPrototypePattern, Pattern.MULTILINE);
        Matcher matcher = pattern.matcher(prototype);
        return matcher.find();
    }
}
