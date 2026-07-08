#include "doctest.h"

#include "entities/cards/Card.hpp"
#include "entities/cards/CreateCards.hpp"
#include "entities/decks/CardDeck.hpp"
#include "entities/decks/CreateCardDeck.hpp"
#include "technical/parsers/SelectedParser.hpp"
#include "technical/rangens/AlwaysFirstSelector.hpp"
#include "technical/rangens/AlwaysLastSelector.hpp"
#include "usecases/cardcomparison/AlwaysFailComparisonStrategy.hpp"
#include "usecases/cardcomparison/BlackRedColourOnlyComparisonStrategy.hpp"
#include "usecases/cardcomparison/ColourCardComparisonStrategy.hpp"
#include "usecases/cardcomparison/CreateCardComparisonStrategy.hpp"
#include "usecases/cardcomparison/ICardComparisonStrategy.hpp"
#include "usecases/cardcomparison/RankCardComparisonStrategy.hpp"
#include "usecases/cardcomparison/StrictCardComparisonStrategy.hpp"

#include <memory>
#include <string>
#include <utility>
#include <vector>

using cardmultigame::technical::parsers::SelectedParser;
using ParsedOrder = std::pair<std::string, std::string>;

using cardmultigame::entities::cards::Card;
using cardmultigame::entities::cards::CreateCards;
using cardmultigame::entities::decks::CardDeck;
using cardmultigame::entities::decks::CreateCardDeck;
using cardmultigame::technical::rangens::AlwaysFirstSelector;
using cardmultigame::technical::rangens::AlwaysLastSelector;
using cardmultigame::technical::rangens::ICardSelector;
using namespace cardmultigame::usecases::cardcomparison;

namespace
{
    std::shared_ptr<Card> makeCard(const std::string& rank, const std::string& colour)
    {
        return std::make_shared<Card>(rank, colour);
    }
}

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

TEST_CASE("t110_parsers_ofCourseParsers")
{
    // Case1: ';' as main delimiter, ',' as second.
    {
        const std::vector<ParsedOrder> ordersExpected = {
            {"Play", "GuessACard"}, {"SetDeck", "JH, QH, KH"}, {"StartGame", ""}, {"Guess", "JH"}, {"Guess", "QH"}};
        const std::string ordersString = "Play GuessACard; SetDeck JH, QH, KH; StartGame; Guess JH; Guess QH";
        assertOrdersEqual(SelectedParser().ProperlyParse(ordersString), ordersExpected);
    }

    // Case2: ',' as main delimiter, ';' as second.
    {
        const std::vector<ParsedOrder> ordersExpected = {
            {"Play", "GuessACard"}, {"SetDeck", "JH; QH; KH"}, {"StartGame", ""}, {"Guess", "JH"}, {"Guess", "QH"}};
        const std::string ordersString = "Play GuessACard, SetDeck JH; QH; KH, StartGame, Guess JH, Guess QH";
        assertOrdersEqual(SelectedParser().ProperlyParse(ordersString), ordersExpected);
    }

    // Case3: '-' as main delimiter, ',' as second.
    {
        const std::vector<ParsedOrder> ordersExpected = {
            {"Play", "GuessACard"}, {"SetDeck", "JH, QH, KH"}, {"StartGame", ""}, {"Guess", "JH"}, {"Guess", "QH"}};
        const std::string ordersString = "Play GuessACard - SetDeck JH, QH, KH - StartGame - Guess JH - Guess QH";
        assertOrdersEqual(SelectedParser().ProperlyParse(ordersString), ordersExpected);
    }
}

TEST_CASE("t101_strategyBasics")
{
    auto card1 = makeCard("J", "H");
    auto identicalCard = makeCard("J", "H");
    auto differentCard = makeCard("K", "H");

    CHECK(StrictCardComparisonStrategy().AreTheSame(card1, identicalCard) == true);
    CHECK(StrictCardComparisonStrategy().AreTheSame(card1, differentCard) == false);
}

TEST_CASE("t102_implementYourOwnStrategy")
{
    auto card1 = makeCard("J", "H");
    auto identicalCard = makeCard("2", "H");
    auto differentCard = makeCard("J", "D");

    CHECK(ColourCardComparisonStrategy().AreTheSame(card1, identicalCard) == true);
    CHECK(ColourCardComparisonStrategy().AreTheSame(card1, differentCard) == false);
}

TEST_CASE("t103_implementTheBlackRedStrategy")
{
    auto reference = makeCard("2", "H");
    auto identical1 = makeCard("2", "H");
    auto identical2 = makeCard("7", "D");
    auto different1 = makeCard("2", "S");
    auto different2 = makeCard("Q", "C");

    CHECK(BlackRedColourOnlyComparisonStrategy().AreTheSame(reference, identical1) == true);
    CHECK(BlackRedColourOnlyComparisonStrategy().AreTheSame(reference, identical2) == true);
    CHECK(BlackRedColourOnlyComparisonStrategy().AreTheSame(reference, different1) == false);
    CHECK(BlackRedColourOnlyComparisonStrategy().AreTheSame(reference, different2) == false);
}

TEST_CASE("t104_powerOfPolymorphism")
{
    auto card1 = makeCard("J", "H");
    auto card2 = makeCard("A", "H");

    std::shared_ptr<ICardComparisonStrategy> strategy;

    strategy = std::make_shared<StrictCardComparisonStrategy>();
    CHECK(strategy->AreTheSame(card1, card2) == false);

    strategy = std::make_shared<ColourCardComparisonStrategy>();
    CHECK(strategy->AreTheSame(card1, card2) == true);

    strategy = std::make_shared<RankCardComparisonStrategy>();
    CHECK(strategy->AreTheSame(card1, card2) == false);

    strategy = std::make_shared<BlackRedColourOnlyComparisonStrategy>();
    CHECK(strategy->AreTheSame(card1, card2) == true);
}

TEST_CASE("t105_factoryMethod_oneStrategyOnly")
{
    auto card1 = makeCard("J", "H");
    auto card2 = makeCard("A", "H");

    auto strategy = CreateCardComparisonStrategy().Create("colour");
    CHECK(strategy->AreTheSame(card1, card2) == true);
}

TEST_CASE("t106_factoryMethod_allStrategies")
{
    auto card1 = makeCard("J", "H");
    auto card2 = makeCard("A", "H");

    CHECK(CreateCardComparisonStrategy().Create("strict")->AreTheSame(card1, card2) == false);
    CHECK(CreateCardComparisonStrategy().Create("colour")->AreTheSame(card1, card2) == true);
    CHECK(CreateCardComparisonStrategy().Create("rank")->AreTheSame(card1, card2) == false);
    CHECK(CreateCardComparisonStrategy().Create("blackred")->AreTheSame(card1, card2) == true);
}

TEST_CASE("t107_nullObjectWeAllLove")
{
    auto card1 = makeCard("J", "H");
    auto card2 = makeCard("A", "H");

    const std::vector<std::shared_ptr<ICardComparisonStrategy>> strategies = {
        CreateCardComparisonStrategy().Create("THIS IS A TYPO!"),
        CreateCardComparisonStrategy().Create(""),
        CreateCardComparisonStrategy().Create("al/fdkafklfhflsdhflhffhfh"),
        CreateCardComparisonStrategy().Create("f;lff;kklfs;df"),
        CreateCardComparisonStrategy().Create("don't else-if those cases please..."),
    };

    for (const auto& strategy : strategies)
    {
        CHECK(strategy->AreTheSame(card1, card2) == false);
    }
}

TEST_CASE("t109_cardDeckNeedsDifferentCreationWays")
{
    auto lowCard = makeCard("2", "C");
    auto highCard = makeCard("K", "H");

    std::shared_ptr<CardDeck> deck = CreateCardDeck().Simple2ToAWith4Colours();
    std::vector<std::shared_ptr<Card>>& allCards = deck->AllCards();

    bool foundSmall = false;
    bool foundLarge = false;
    for (const auto& card : allCards)
    {
        if (StrictCardComparisonStrategy().AreTheSame(card, lowCard)) foundSmall = true;
        if (StrictCardComparisonStrategy().AreTheSame(card, highCard)) foundLarge = true;
    }

    CHECK(foundSmall == true);
    CHECK(foundLarge == true);
}

TEST_CASE("t111_cardDeckCanHaveConfiguredRandomGenerator_first")
{
    auto selector = std::make_shared<AlwaysFirstSelector>();
    std::vector<std::shared_ptr<Card>> expectedCards = CreateCards().CreateCollection("9H, 10H, 9C, 10C, AD");

    std::vector<std::shared_ptr<Card>> copiedList = expectedCards;
    CardDeck deck(selector, copiedList);

    std::vector<std::shared_ptr<Card>> actualCards;
    for (int i = 0; i < 5; ++i)
    {
        actualCards.push_back(deck.DrawRandomCard());
    }

    for (int i = 0; i < 5; ++i)
    {
        CHECK(expectedCards[i]->Colour() == actualCards[i]->Colour());
        CHECK(expectedCards[i]->Rank() == actualCards[i]->Rank());
    }
}

TEST_CASE("t112_cardDeckCanHaveConfiguredRandomGenerator_last")
{
    auto selector = std::make_shared<AlwaysLastSelector>();
    std::vector<std::shared_ptr<Card>> expectedCards = CreateCards().CreateCollection("9H, 10H, 9C, 10C, AD");

    std::vector<std::shared_ptr<Card>> copiedList = expectedCards;
    CardDeck deck(selector, copiedList);

    std::vector<std::shared_ptr<Card>> actualCards;
    for (int i = 0; i < 5; ++i)
    {
        actualCards.push_back(deck.DrawRandomCard());
    }

    for (int i = 0; i < 5; ++i)
    {
        CHECK(expectedCards[4 - i]->Colour() == actualCards[i]->Colour());
        CHECK(expectedCards[4 - i]->Rank() == actualCards[i]->Rank());
    }
}

TEST_CASE("t113_cardDeckFactory_canReconfigureRandomGenerator")
{
    const std::string inputCardSigils = "JS, QH, KD, AC";

    std::vector<std::shared_ptr<Card>> expectedCards = CreateCards().CreateCollection(inputCardSigils);

    CreateCardDeck creator;

    creator.SetCardSelector(std::make_shared<AlwaysFirstSelector>());
    std::shared_ptr<CardDeck> deckWithAlwaysFirst = creator.FromGivenCards(inputCardSigils);

    std::vector<std::shared_ptr<Card>> actualFirstCards;
    for (int i = 0; i < 4; ++i)
    {
        actualFirstCards.push_back(deckWithAlwaysFirst->DrawRandomCard());
    }
    for (int i = 0; i < 4; ++i)
    {
        CHECK(expectedCards[i]->Colour() == actualFirstCards[i]->Colour());
        CHECK(expectedCards[i]->Rank() == actualFirstCards[i]->Rank());
    }

    creator.SetCardSelector(std::make_shared<AlwaysLastSelector>());
    std::shared_ptr<CardDeck> deckWithAlwaysLast = creator.FromGivenCards(inputCardSigils);

    std::vector<std::shared_ptr<Card>> actualLastCards;
    for (int i = 0; i < 4; ++i)
    {
        actualLastCards.push_back(deckWithAlwaysLast->DrawRandomCard());
    }
    for (int i = 0; i < 4; ++i)
    {
        CHECK(expectedCards[3 - i]->Colour() == actualLastCards[i]->Colour());
        CHECK(expectedCards[3 - i]->Rank() == actualLastCards[i]->Rank());
    }
}
