using Core.Interface;
using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Text;

namespace CoreTests
{
    class TestEndToEnd
    {
        [Test]
        public void SimpleVariantHasProperSetup()
        {
            // Given
            string input = "SETUP cat; Play GuessACard;";

            var dispatcher = new UiLogicDispatcher();

            // When
            dispatcher.SetupGame(input);

            // Then
            string result = dispatcher.DisplayCurrentState();

            Assert.IsTrue(result.Contains("[CurrentTurnNumber, 0]"));
            Assert.IsTrue(result.Contains("[MaximumTurns, 5]"));

        }

        [Test]
        public void WithVariantHasProperSetup()
        {
            // Given
            string input = "SETUP dog; Play GuessACard; GameVariant RedBlack;";

            var dispatcher = new UiLogicDispatcher();

            // When
            dispatcher.SetupGame(input);

            // Then
            string result = dispatcher.DisplayCurrentState();

            Assert.IsTrue(result.Contains("[CurrentTurnNumber, 0]"));
            Assert.IsTrue(result.Contains("[MaximumTurns, 5]"));

        }

    }
}
