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

    public class TestBlackjack
    {

        [Test]
        public void BlackjackHappyPath__Kings_DDDP_Victory()
        {
            // Given primitives
            var cards = new List<string> { "KS", "KH", "KD", "KC" };

            var secondSeparator = ",";
            string cardsInDeck = string.Join(secondSeparator, cards);

            var configOrders = "Play Blackjack; SetDeck " + cardsInDeck + "; SETUP; ";
            var gameOrders = "Draw; Draw; Draw; Pass;";   // 0 -> 6 -> 12 -> 18 -> PASS: Victory

            // Given
            string orders = configOrders + gameOrders;

            GameManager gm = new CreateGameManager().DefaultsWithOrders(orders);

            // When
            gm.ExecuteOrders(orders);
            GameState resultReceived = gm.CurrentState();

            // Then
            Assert.IsTrue(QueryGameState.GameUndergoing(resultReceived) == "Victory");

        }

        [Test]
        public void BlackjackHappyPath__Kings_DDDD_Loss()
        {
            // Given primitives
            var cards = new List<string> { "KS", "KH", "KD", "KC" };

            var secondSeparator = ",";
            string cardsInDeck = string.Join(secondSeparator, cards);

            var configOrders = "Play Blackjack; SetDeck " + cardsInDeck + "; SETUP; ";
            var gameOrders = "Draw; Draw; Draw; Draw;";   // 0 -> 6 -> 12 -> 18 -> defeat: 24

            // Given
            string orders = configOrders + gameOrders;

            GameManager gm = new CreateGameManager().DefaultsWithOrders(orders);

            // When
            gm.ExecuteOrders(orders);
            GameState resultReceived = gm.CurrentState();

            // Then
            Assert.IsTrue(QueryGameState.GameUndergoing(resultReceived) == "Defeat");

        }

        [Test]
        public void BlackjackHappyPath__Kings_DDP_Loss()
        {
            // Given primitives
            var cards = new List<string> { "KS", "KH", "KD", "KC" };

            var secondSeparator = ",";
            string cardsInDeck = string.Join(secondSeparator, cards);

            var configOrders = "Play Blackjack; SetDeck " + cardsInDeck + "; SETUP; ";
            var gameOrders = "Draw; Draw; Pass;";   // 0 -> 6 -> 12 -> PASS : defeat (future = 18)

            // Given
            string orders = configOrders + gameOrders;

            GameManager gm = new CreateGameManager().DefaultsWithOrders(orders);

            // When
            gm.ExecuteOrders(orders);
            GameState resultReceived = gm.CurrentState();

            // Then
            Assert.IsTrue(QueryGameState.GameUndergoing(resultReceived) == "Defeat");

        }

    }
}
