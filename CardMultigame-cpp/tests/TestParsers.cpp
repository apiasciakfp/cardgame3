#include "doctest.h"

#include "technical/parsers/SelectedParser.hpp"

#include <string>
#include <utility>
#include <vector>

using cardmultigame::technical::parsers::SelectedParser;
using ParsedOrder = std::pair<std::string, std::string>;

namespace
{
    void assertOrdersEqual(const std::vector<ParsedOrder>& received, const std::vector<ParsedOrder>& expected)
    {
        REQUIRE(received.size() == expected.size());
        for (std::size_t i = 0; i < expected.size(); ++i)
        {
            CHECK(received[i].first == expected[i].first);
            CHECK(received[i].second == expected[i].second);
        }
    }
}

TEST_CASE("parserProperlySelected_semicolonSeparator")
{
    const std::vector<ParsedOrder> ordersExpected = {
        {"Play", "GuessACard"},
        {"SetDeck", "JH, QH, KH"},
        {"StartGame", ""},
        {"Guess", "JH"},
        {"Guess", "QH"},
    };

    const std::string ordersString = "Play GuessACard; SetDeck JH, QH, KH; StartGame; Guess JH; Guess QH";

    const std::vector<ParsedOrder> ordersReceived = SelectedParser().ProperlyParse(ordersString);

    assertOrdersEqual(ordersReceived, ordersExpected);
}

TEST_CASE("parserProperlySelected_commaSeparator")
{
    const std::vector<ParsedOrder> ordersExpected = {
        {"Play", "GuessACard"},
        {"SetDeck", "JH; QH; KH"},
        {"StartGame", ""},
        {"Guess", "JH"},
        {"Guess", "QH"},
    };

    const std::string ordersString = "Play GuessACard, SetDeck JH; QH; KH, StartGame, Guess JH, Guess QH";

    const std::vector<ParsedOrder> ordersReceived = SelectedParser().ProperlyParse(ordersString);

    assertOrdersEqual(ordersReceived, ordersExpected);
}
