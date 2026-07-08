#include "doctest.h"

#include "entities/cards/Card.hpp"
#include "entities/cards/CreateCards.hpp"
#include "entities/decks/CardDeck.hpp"
#include "entities/decks/CreateCardDeck.hpp"
#include "usecases/cardcomparison/StrictCardComparisonStrategy.hpp"

#include <memory>
#include <string>
#include <vector>

using cardmultigame::entities::cards::Card;
using cardmultigame::entities::cards::CreateCards;
using cardmultigame::entities::decks::CardDeck;
using cardmultigame::entities::decks::CreateCardDeck;
using cardmultigame::usecases::cardcomparison::StrictCardComparisonStrategy;

TEST_CASE("drawCardFromDeck_randomly_5CardsUntil0Left")
{
    const std::vector<std::string> cardSigils = {"9H", "10H", "JH", "QH", "KH"};
    const std::string cardsInDeck = "9H,10H,JH,QH,KH";

    std::vector<std::shared_ptr<Card>> cards = CreateCards().CreateCollection(cardsInDeck);
    std::shared_ptr<CardDeck> deck = CreateCardDeck().FromGivenCards(cardsInDeck);

    const int lengthInDeck = 0;
    const std::size_t lengthOfDrawnCards = cards.size();

    std::vector<std::shared_ptr<Card>> drawnCards;
    for (std::size_t i = 0; i < cardSigils.size(); ++i)
    {
        drawnCards.push_back(deck->DrawRandomCard());
    }

    std::vector<std::shared_ptr<Card>>& cardsRemaining = deck->AllCards();

    CHECK(static_cast<int>(cardsRemaining.size()) == lengthInDeck);
    CHECK(drawnCards.size() == lengthOfDrawnCards);
}

TEST_CASE("createDeck_withStandardCards9ToAWith4Colours")
{
    const int cardCountExpected = 24;

    std::shared_ptr<CardDeck> deck = CreateCardDeck().Simple9ToAWith4Colours();

    std::vector<std::shared_ptr<Card>>& cardsReceived = deck->AllCards();

    CHECK(static_cast<int>(cardsReceived.size()) == cardCountExpected);
}

TEST_CASE("createDeck_with3SetCards_inCommaFormat")
{
    const std::string cardsInDeck = "JH,QH,KH";

    std::vector<std::shared_ptr<Card>> cardsExpected = CreateCards().CreateCollection(cardsInDeck);

    std::shared_ptr<CardDeck> deck = CreateCardDeck().FromGivenCards(cardsInDeck);

    std::vector<std::shared_ptr<Card>>& cardsReceived = deck->AllCards();

    REQUIRE(cardsExpected.size() == cardsReceived.size());

    for (std::size_t i = 0; i < cardsExpected.size(); ++i)
    {
        CHECK(StrictCardComparisonStrategy().AreTheSame(cardsExpected[i], cardsReceived[i]));
    }
}
