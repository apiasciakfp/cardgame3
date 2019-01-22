using Core.Technical.Parsers;
using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CoreCasinoTests.Technical
{

    public class TestParsers
    {
        [Test]
        public void ParserProperlySelected__SemicolonSeparator()
        {
            // Expecting
            List<Tuple<string, string>> ordersExpected = new List<Tuple<string, string>>
            {
                new Tuple<string, string>("Play", "GuessACard"),
                new Tuple<string, string>("SetDeck", "JH, QH, KH"),
                new Tuple<string, string>("StartGame", ""),
                new Tuple<string, string>("Guess", "JH"),
                new Tuple<string, string>("Guess", "QH"),
            };

            // Given
            string ordersString = "Play GuessACard; SetDeck JH, QH, KH; StartGame; Guess JH; Guess QH";

            // When
            List<Tuple<string, string>> ordersReceived = new SelectedParser().ProperlyParse(ordersString);

            // Then
            for(int i=0; i< ordersExpected.Count; i++)
            {
                Assert.AreEqual(ordersExpected[i], ordersReceived[i]);
            }
        }

        [Test]
        public void ParserProperlySelected__CommaSeparator()
        {
            // Expecting
            List<Tuple<string, string>> ordersExpected = new List<Tuple<string, string>>
            {
                new Tuple<string, string>("Play", "GuessACard"),
                new Tuple<string, string>("SetDeck", "JH; QH; KH"),
                new Tuple<string, string>("StartGame", ""),
                new Tuple<string, string>("Guess", "JH"),
                new Tuple<string, string>("Guess", "QH"),
            };

            // Given
            string ordersString = "Play GuessACard, SetDeck JH; QH; KH, StartGame, Guess JH, Guess QH";

            // When
            List<Tuple<string, string>> ordersReceived = new SelectedParser().ProperlyParse(ordersString);

            // Then
            for (int i = 0; i < ordersExpected.Count; i++)
            {
                Assert.AreEqual(ordersExpected[i], ordersReceived[i]);
            }
        }
        
    }
}
