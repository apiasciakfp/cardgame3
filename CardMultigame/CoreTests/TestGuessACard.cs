using System;
using Core.Entities.Decks;
using System.Collections.Generic;
using Core.Interfaces.GameManagers;
using Core.Entities.GameStates;
using Core.Entities.Cards;
using Core.Usecases.InfluenceState;
using NUnit.Framework;

namespace CoreCasinoTests
{

    public class TestGuessACard
    {

        [Test]
        public void DirectCardGuessingWorks__ForThreeCardsDeck__Failure()
        {
            // Given primitives
            var cards = new List<string> { "JH", "QH", "KH" };
            var cardOutsideDeck = "2C";
            var secondSeparator = ",";
            string cardsInDeck = string.Join(secondSeparator, cards);

            // Given
            string orders = "Play GuessACard; SetDeck " + cardsInDeck + "; SetMaxTurns 3; " +
                "Guess " + cardOutsideDeck + "; Guess " + cardOutsideDeck + "; Guess " + cardOutsideDeck;

            GameManager gm = new CreateGameManager().DefaultsWithOrders(orders);

            // When
            gm.ExecuteOrders(orders);
            GameState resultReceived = gm.CurrentState();

            // Then
            Assert.IsTrue(QueryGameState.GameUndergoing(resultReceived) == "Defeat");
            Assert.IsTrue(QueryGameState.MaximumTurns(resultReceived) == QueryGameState.CurrentTurn(resultReceived));
            Assert.IsTrue(QueryGameState.AmountOfCardsLeft(resultReceived) == 0);

        }

        [Test]
        public void DirectCardGuessingWorks__ForThreeCardsDeck__Failure_DiffSeparators()
        {
            // Given primitives
            var cards = new List<string> { "JH", "QH", "KH" };
            var cardOutsideDeck = "2C";
            var secondSeparator = ";";
            string cardsInDeck = string.Join(secondSeparator, cards);

            // Given
            string orders = "Play GuessACard, SetDeck " + cardsInDeck  + ", SetMaxTurns 3, " + 
                "Guess " + cardOutsideDeck + ", Guess " + cardOutsideDeck + ", Guess " + cardOutsideDeck;

            GameManager gm = new CreateGameManager().DefaultsWithOrders(orders);

            // When
            gm.ExecuteOrders(orders);
            GameState resultReceived = gm.CurrentState();

            // Then
            Assert.IsTrue(QueryGameState.GameUndergoing(resultReceived) == "Defeat");
            Assert.IsTrue(QueryGameState.MaximumTurns(resultReceived) == QueryGameState.CurrentTurn(resultReceived));
            Assert.IsTrue(QueryGameState.AmountOfCardsLeft(resultReceived) == 0);

        }

        [Test]
        public void DirectCardGuessingWorks__ForThreeCardsDeck__Victory()
        {
            // Given primitives
            var cards = new List<string> { "JH", "QH", "KH" };
            var cardInsideDeck = "JH";
            var secondSeparator = ",";
            string cardsInDeck = string.Join(secondSeparator, cards);

            // Given
            string orders = "Play GuessACard; SetDeck " + cardsInDeck + "; SetMaxTurns 3; " +
                "Guess " + cardInsideDeck + "; Guess " + cardInsideDeck + "; Guess " + cardInsideDeck;

            GameManager gm = new CreateGameManager().DefaultsWithOrders(orders);

            // When
            gm.ExecuteOrders(orders);
            GameState resultReceived = gm.CurrentState();

            // Then
            Assert.IsTrue(QueryGameState.GameUndergoing(resultReceived) == "Victory");

        }

        [Test]
        public void CardRedBlackGuessingWorks__ForThreeCardsOneColourDeck_MissMissVictory()
        {
            // Given primitives
            var cards = new List<string> { "JH", "QH", "KH" };
            var cardOutsideDeck = "2C";
            var cardInsideDeck = "2D";
            var secondSeparator = ",";
            string cardsInDeck = string.Join(secondSeparator, cards);

            // Given
            string orders = "Play GuessACard; SetDeck " + cardsInDeck + "; GameVariant RedBlack; " +
                "Guess " + cardOutsideDeck + "; Guess " + cardOutsideDeck + "; Guess " + cardInsideDeck;

            GameManager gm = new CreateGameManager().DefaultsWithOrders(orders);

            // When
            gm.ExecuteOrders(orders);
            GameState resultReceived = gm.CurrentState();

            // Then
            Assert.IsTrue(QueryGameState.GameUndergoing(resultReceived) == "Victory", "We received: " + 
                QueryGameState.GameUndergoing(resultReceived));

        }

    }
}
