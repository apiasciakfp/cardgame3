#include "doctest.h"

#include "entities/gamestates/GameState.hpp"
#include "gamemanagers/CreateGameManager.hpp"
#include "gamemanagers/GameManager.hpp"
#include "usecases/influencestate/QueryGameState.hpp"

#include <string>

using namespace cardmultigame;
using entities::gamestates::GameState;
using gamemanagers::CreateGameManager;
using gamemanagers::GameManager;
using Query = usecases::influencestate::QueryGameState;

TEST_CASE("directCardGuessingWorks_forThreeCardsDeck_failure")
{
    const std::string cardsInDeck = "JH,QH,KH";
    const std::string cardOutsideDeck = "2C";
    const std::string orders = "Play GuessACard; SetDeck " + cardsInDeck + "; SetMaxTurns 3; " +
                               "Guess " + cardOutsideDeck + "; Guess " + cardOutsideDeck + "; Guess " + cardOutsideDeck;

    GameManager gm = CreateGameManager().DefaultsWithOrders(orders);
    gm.ExecuteOrders(orders);
    GameState& resultReceived = gm.CurrentState();

    CHECK(Query::GameUndergoing(resultReceived) == "Defeat");
    CHECK(Query::MaximumTurns(resultReceived) == Query::CurrentTurn(resultReceived));
    CHECK(Query::AmountOfCardsLeft(resultReceived) == 0);
}

TEST_CASE("directCardGuessingWorks_forThreeCardsDeck_failure_diffSeparators")
{
    const std::string cardsInDeck = "JH;QH;KH";
    const std::string cardOutsideDeck = "2C";
    const std::string orders = "Play GuessACard, SetDeck " + cardsInDeck + ", SetMaxTurns 3, " +
                               "Guess " + cardOutsideDeck + ", Guess " + cardOutsideDeck + ", Guess " + cardOutsideDeck;

    GameManager gm = CreateGameManager().DefaultsWithOrders(orders);
    gm.ExecuteOrders(orders);
    GameState& resultReceived = gm.CurrentState();

    CHECK(Query::GameUndergoing(resultReceived) == "Defeat");
    CHECK(Query::MaximumTurns(resultReceived) == Query::CurrentTurn(resultReceived));
    CHECK(Query::AmountOfCardsLeft(resultReceived) == 0);
}

TEST_CASE("directCardGuessingWorks_forThreeCardsDeck_victory")
{
    const std::string cardsInDeck = "JH,QH,KH";
    const std::string cardInsideDeck = "JH";
    const std::string orders = "Play GuessACard; SetDeck " + cardsInDeck + "; SetMaxTurns 3; " +
                               "Guess " + cardInsideDeck + "; Guess " + cardInsideDeck + "; Guess " + cardInsideDeck;

    GameManager gm = CreateGameManager().DefaultsWithOrders(orders);
    gm.ExecuteOrders(orders);
    GameState& resultReceived = gm.CurrentState();

    CHECK(Query::GameUndergoing(resultReceived) == "Victory");
}

TEST_CASE("cardRedBlackGuessingWorks_forThreeCardsOneColourDeck_missMissVictory")
{
    const std::string cardsInDeck = "JH,QH,KH";
    const std::string cardOutsideDeck = "2C";
    const std::string cardInsideDeck = "2D";
    const std::string orders = "Play GuessACard; SetDeck " + cardsInDeck + "; GameVariant RedBlack; " +
                               "Guess " + cardOutsideDeck + "; Guess " + cardOutsideDeck + "; Guess " + cardInsideDeck;

    GameManager gm = CreateGameManager().DefaultsWithOrders(orders);
    gm.ExecuteOrders(orders);
    GameState& resultReceived = gm.CurrentState();

    CHECK(Query::GameUndergoing(resultReceived) == "Victory");
}
