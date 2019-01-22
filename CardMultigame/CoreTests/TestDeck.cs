using Core.Entities.Cards;
using Core.Entities.Decks;
using Core.Usecases.CardComparison;
using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CoreCasinoTests.Entities
{

    public class TestDeck
    {
        [Test]
        public void DrawCardFromDeck__Randomly__5CardsUntil0Left()
        {
            // Given
            var cardSigils = new List<string> { "9H", "10H", "JH", "QH", "KH" };
            var separator = ",";
            string cardsInDeck = string.Join(separator, cardSigils);

            List<Card> cards = new CreateCards().CreateCollection(cardsInDeck);
            CardDeck deck = new CreateCardDeck().FromGivenCards(cardsInDeck);

            // Expecting 
            int lengthInDeck = 0;
            int lengthOfDrawnCards = cards.Count();

            // When
            List<Card> drawnCards = new List<Card>();
            for(int i=0;i<cardSigils.Count();i++)
            {
                drawnCards.Add(deck.DrawRandomCard());
            }

            // Then
            List<Card> cardsRemaining = deck.AllCards();

            Assert.IsTrue(lengthInDeck == cardsRemaining.Count());
            Assert.IsTrue(lengthOfDrawnCards == drawnCards.Count());

        }


        [Test]
        public void CreateDeck__WithStandardCards9ToAWith4Colours()
        {
            // Given
            // Expecting
            int cardCountExpected = 24;

            // When
            CardDeck deck = new CreateCardDeck().Simple9ToAWith4Colours();

            // Then
            List<Card> cardsReceived = deck.AllCards();

            Assert.IsTrue(cardsReceived.Count() == cardCountExpected);
        }

        [Test]
        public void CreateDeck__With3SetCards_InCommaFormat()
        {
            // Given
            var cards = new List<string> { "JH", "QH", "KH" };
            var separator = ",";
            string cardsInDeck = string.Join(separator, cards);

            // Expecting 
            List<Card> cardsExpected = new CreateCards().CreateCollection(cardsInDeck);

            // When
            CardDeck deck = new CreateCardDeck().FromGivenCards(cardsInDeck);

            // Then
            List<Card> cardsReceived = deck.AllCards();

            Assert.IsTrue(cardsExpected.Count() == cardsReceived.Count());
            
            for(int i=0; i< cardsExpected.Count(); i++)
            {
                Assert.IsTrue(new StrictCardComparisonStrategy().AreTheSame(cardsExpected[i], cardsReceived[i]));
            }
        }
    }
}
