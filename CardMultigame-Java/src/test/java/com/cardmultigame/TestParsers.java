package com.cardmultigame;

import com.cardmultigame.technical.parsers.ParsedOrder;
import com.cardmultigame.technical.parsers.SelectedParser;
import org.junit.jupiter.api.Test;
import java.util.List;
import static org.assertj.core.api.Assertions.assertThat;

class TestParsers {

    @Test
    void parserProperlySelected_semicolonSeparator() {
        // Expecting
        List<ParsedOrder> ordersExpected = List.of(
            new ParsedOrder("Play", "GuessACard"),
            new ParsedOrder("SetDeck", "JH, QH, KH"),
            new ParsedOrder("StartGame", ""),
            new ParsedOrder("Guess", "JH"),
            new ParsedOrder("Guess", "QH")
        );

        // Given
        String ordersString = "Play GuessACard; SetDeck JH, QH, KH; StartGame; Guess JH; Guess QH";

        // When
        List<ParsedOrder> ordersReceived = new SelectedParser().properlyParse(ordersString);

        // Then
        for (int i = 0; i < ordersExpected.size(); i++) {
            assertThat(ordersReceived.get(i)).isEqualTo(ordersExpected.get(i));
        }
    }

    @Test
    void parserProperlySelected_commaSeparator() {
        // Expecting
        List<ParsedOrder> ordersExpected = List.of(
            new ParsedOrder("Play", "GuessACard"),
            new ParsedOrder("SetDeck", "JH; QH; KH"),
            new ParsedOrder("StartGame", ""),
            new ParsedOrder("Guess", "JH"),
            new ParsedOrder("Guess", "QH")
        );

        // Given
        String ordersString = "Play GuessACard, SetDeck JH; QH; KH, StartGame, Guess JH, Guess QH";

        // When
        List<ParsedOrder> ordersReceived = new SelectedParser().properlyParse(ordersString);

        // Then
        for (int i = 0; i < ordersExpected.size(); i++) {
            assertThat(ordersReceived.get(i)).isEqualTo(ordersExpected.get(i));
        }
    }
}
