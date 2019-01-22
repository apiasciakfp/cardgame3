using Core.Entities.Cards;
using Core.Entities.Decks;
using Core.Entities.Games;
using Core.Technical.Parsers;
using Core.Technical.RanGens;
using Core.Usecases.CardComparison;
using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TrainingTests
{

    public class Batch_100
    {
        [Test]
        public void T_101_StrategyBasics()
        {
            // Commentary
            // ---
            // The first test should pass. You are dealing with something, which compares two Cards.
            // ---

            // Given
            Card card1 = new Card("J", "H");
            Card identicalCard = new Card("J", "H");
            Card differentCard = new Card("K", "H");

            // When
            bool areTheSameWithIdentical = new StrictCardComparisonStrategy().AreTheSame(card1, identicalCard);
            bool areTheSameWithDifferent = new StrictCardComparisonStrategy().AreTheSame(card1, differentCard);

            // Then
            Assert.IsTrue(areTheSameWithIdentical);
            Assert.IsFalse(areTheSameWithDifferent);
        }

        [Test]
        public void T_102_ImplementYourOwnStrategy()
        {
            // Commentary
            // ---
            // This test fails. Your role is to create a Strategy which will pass this test.
            // We want to check ONLY card colours, like in the example below.
            // ---

            // Given
            Card card1 = new Card("J", "H");
            Card identicalCard = new Card("2", "H");
            Card differentCard = new Card("J", "D");

            // When
            bool areTheSameWithIdentical = new ColourCardComparisonStrategy().AreTheSame(card1, identicalCard);
            bool areTheSameWithDifferent = new ColourCardComparisonStrategy().AreTheSame(card1, differentCard);

            // Then
            Assert.IsTrue(areTheSameWithIdentical);
            Assert.IsFalse(areTheSameWithDifferent);
        }

        [Test]
        public void T_103_ImplementTheBlackRedStrategy()
        {
            // Commentary
            // ---
            // To be able to create game modifiers, we need a new comparator. A strategy which checks
            // if the card is Black or Red. The type of card is irrelevant.
            // Spades, Clubs (S, C) -> black
            // Hearts, Diamonds (H, D) -> red
            // ---

            // Given
            Card reference = new Card("2", "H");
            Card identical_1 = new Card("2", "H");
            Card identical_2 = new Card("7", "D");
            Card different_1 = new Card("2", "S");
            Card different_2 = new Card("Q", "C");

            // When
            bool areIdentical_1 = new BlackRedColourOnlyComparisonStrategy().AreTheSame(reference, identical_1);
            bool areIdentical_2 = new BlackRedColourOnlyComparisonStrategy().AreTheSame(reference, identical_2);
            bool areDifferent_1 = new BlackRedColourOnlyComparisonStrategy().AreTheSame(reference, different_1);
            bool areDifferent_2 = new BlackRedColourOnlyComparisonStrategy().AreTheSame(reference, different_2);

            // Then
            Assert.IsTrue(areIdentical_1);
            Assert.IsTrue(areIdentical_2);
            Assert.IsFalse(areDifferent_1);
            Assert.IsFalse(areDifferent_2);
        }

        [Test]
        public void T_104_PowerOfPolymorphism()
        {
            // Commentary
            // ---
            // The power of strategy is the power of polymorphism.
            // Note: the same card pair will be treated differently by different comparators.
            // Implement a new strategy, one which will look at the rank only.
            // ---

            // Given general
            Card card1 = new Card("J", "H");
            Card card2 = new Card("A", "H");

            ICardComparisonStrategy strategy;

            // Should pass.
            strategy = new StrictCardComparisonStrategy();
            bool areTheSame_Strict = strategy.AreTheSame(card1, card2);
            Assert.IsFalse(areTheSame_Strict);

            // Should pass. Note: SAME strategy reference, different implementation.
            strategy = new ColourCardComparisonStrategy();
            bool areTheSame_Colour = strategy.AreTheSame(card1, card2);
            Assert.IsTrue(areTheSame_Colour);

            // This is what you will implement
            strategy = new RankCardComparisonStrategy();
            bool areTheSame_Rank = strategy.AreTheSame(card1, card2);
            Assert.IsFalse(areTheSame_Rank);

            // Should pass again.
            strategy = new BlackRedColourOnlyComparisonStrategy();
            bool areTheSame_BlackRed = strategy.AreTheSame(card1, card2);
            Assert.IsTrue(areTheSame_BlackRed);
        }

        [Test]
        public void T_105_FactoryMethod_OneStrategyOnly()
        {
            // Commentary
            // ---
            // This moves us neatly into Factory Method pattern.
            // Note: if we can use a reference, we can move the stuff outside.
            // ---

            // Given - same scenario
            Card card1 = new Card("J", "H");
            Card card2 = new Card("A", "H");

            //...with a twist:
            ICardComparisonStrategy strategy = new CreateCardComparisonStrategy().Create("colour");

            // When
            bool areTheSame_Strict = strategy.AreTheSame(card1, card2);

            // Then
            Assert.IsTrue(areTheSame_Strict);

        }

        [Test]
        public void T_106_FactoryMethod_AllStrategies()
        {
            // Commentary
            // ---
            // Remember test 104? Excellent; now, let's hide it behind the factory.
            // Time to see how factory and strategies work together neatly.
            // ---

            // Given general
            Card card1 = new Card("J", "H");
            Card card2 = new Card("A", "H");

            ICardComparisonStrategy strategy;

            // Strict
            strategy = new CreateCardComparisonStrategy().Create("strict");
            bool areTheSame_Strict = strategy.AreTheSame(card1, card2);
            Assert.IsFalse(areTheSame_Strict);

            // Colour
            strategy = new CreateCardComparisonStrategy().Create("colour");
            bool areTheSame_Colour = strategy.AreTheSame(card1, card2);
            Assert.IsTrue(areTheSame_Colour);

            // Rank
            strategy = new CreateCardComparisonStrategy().Create("rank");
            bool areTheSame_Rank = strategy.AreTheSame(card1, card2);
            Assert.IsFalse(areTheSame_Rank);

            // BlackRed
            strategy = new CreateCardComparisonStrategy().Create("blackred");
            bool areTheSame_BlackRed = strategy.AreTheSame(card1, card2);
            Assert.IsTrue(areTheSame_BlackRed);

        }

        [Test]
        public void T_107_NullObjectWeAllLove()
        {
            // Commentary
            // ---
            // What happens if we make a mistake? What if we have a typo? Any typo?
            // I would like to have a new Strategy returned. One
            // ---

            // Given - same scenario
            Card card1 = new Card("J", "H");
            Card card2 = new Card("A", "H");

            // When
            List<ICardComparisonStrategy> strategies = new List<ICardComparisonStrategy>()
            {
                new CreateCardComparisonStrategy().Create("THIS IS A TYPO!"),
                new CreateCardComparisonStrategy().Create(""),
                new CreateCardComparisonStrategy().Create("al/fdkafklfhflsdhflhffhfh"),
                new CreateCardComparisonStrategy().Create("f;lff;kklfs;df"),
                new CreateCardComparisonStrategy().Create("don't else-if those cases please...")
            };

            // When, Then
            foreach (var strategy in strategies)
            {
                Assert.IsFalse(strategy.AreTheSame(card1, card2));
            }

        }

        [Test]
        public void T_108_LetsPrepareTheStrategyForTheFuture()
        {
            // Commentary
            // ---
            // The program doesn't work at this moment. One of the missing things is the lack of 
            // comparison strategy for a GuessACardGame we want to activate.
            // Let's put it there. Do not worry about other code out there; we'll get to it.
            // GuessACardGame uses a Strict strategy
            // ---

            // Given - nothing
            // When
            ICardComparisonStrategy selectedStrategy = new GuessACardGame().CardComparisonStrategy();

            // Then
            Assert.IsTrue(selectedStrategy is StrictCardComparisonStrategy);

        }

        [Test]
        public void T_109_CardDeckNeedsDifferentCreationWays()
        {
            // Commentary
            // ---
            // It is pointless to have card games without a card deck. So we have to make one for ourselves.
            // CardDeck class does fortunately exist already, but it needs to be filled with default methods.
            // Some cards, like Bridge or Tarot use a 2-A spread. Some other cards use a 9-A spread.
            // GuessACard game uses a 9-A spread. So let's implement the 2-A spread in CreateCardDeck, too.
            //
            // Note, that CreateCardDeck is a FACTORY. Depending on what we need, we will use different 
            // creation methods. So factories are more than just 'connected with polymorphism' - CardDeck
            // will simply be filled in different ways.
            //
            // Also note we could implement CreateCardDeck methods as different strategies ;-). If you don't
            // understand this, ask me. I will explain.
            // ---

            // Expecting
            int cardsBetween_2_A = 13;
            int cardColours = 4;
            int totalCards = cardsBetween_2_A * cardColours;

            Card lowCard = new Card("2", "C");
            Card highCard = new Card("K", "H");

            // When
            CardDeck deck = new CreateCardDeck().Simple2ToAWith4Colours();

            // Then
            List<Card> allCards = deck.AllCards();

            bool foundSmall = false;
            bool foundLarge = false;

            foreach (var card in allCards)
            {
                if (new StrictCardComparisonStrategy().AreTheSame(card, lowCard)) foundSmall = true;
                if (new StrictCardComparisonStrategy().AreTheSame(card, highCard)) foundLarge = true;
            }

            Assert.IsTrue(foundSmall);
            Assert.IsTrue(foundLarge);
        }

        [Test]
        public void T_110_Parsers_OfCourseParsers()
        {
            // Commentary
            // ---
            // Time for a real world scenario.
            // Look at the string below (orderString, two cases) and note how they get elegantly parsed.
            // You will have to create a parsing strategy in such a way that (order3 and order4) will
            // also pass successfully.
            // You will not have to change a lot of existing code, but you will have to find where are the
            // creation methods (factory methods) and how does the selection take place.
            // ---


            List<Tuple<string, string>> ordersExpected;
            string ordersString;
            List<Tuple<string, string>> ordersReceived;

            // ---
            // This passes. Case1: ';' as main delimiter, ',' as second.
            // ---

            // Expecting
            ordersExpected = new List<Tuple<string, string>>
            {
                new Tuple<string, string>("Play", "GuessACard"),
                new Tuple<string, string>("SetDeck", "JH, QH, KH"),
                new Tuple<string, string>("StartGame", ""),
                new Tuple<string, string>("Guess", "JH"),
                new Tuple<string, string>("Guess", "QH"),
            };

            // Given
            ordersString = "Play GuessACard; SetDeck JH, QH, KH; StartGame; Guess JH; Guess QH";

            // When
            ordersReceived = new SelectedParser().ProperlyParse(ordersString);

            // Then
            for (int i = 0; i < ordersExpected.Count; i++)
            {
                Assert.AreEqual(ordersExpected[i], ordersReceived[i]);
            }

            // ---
            // This passes. Case2: ',' as main delimiter, ';' as second.
            // ---

            // Expecting
            ordersExpected = new List<Tuple<string, string>>
            {
                new Tuple<string, string>("Play", "GuessACard"),
                new Tuple<string, string>("SetDeck", "JH; QH; KH"),
                new Tuple<string, string>("StartGame", ""),
                new Tuple<string, string>("Guess", "JH"),
                new Tuple<string, string>("Guess", "QH"),
            };

            // Given
            ordersString = "Play GuessACard, SetDeck JH; QH; KH, StartGame, Guess JH, Guess QH";

            // When
            ordersReceived = new SelectedParser().ProperlyParse(ordersString);

            // Then
            for (int i = 0; i < ordersExpected.Count; i++)
            {
                Assert.AreEqual(ordersExpected[i], ordersReceived[i]);
            }

            // ---
            // This does not pass.
            // Case3: '-' as main delimiter, ',' as second.
            // ---

            // Expecting
            ordersExpected = new List<Tuple<string, string>>
            {
                new Tuple<string, string>("Play", "GuessACard"),
                new Tuple<string, string>("SetDeck", "JH, QH, KH"),
                new Tuple<string, string>("StartGame", ""),
                new Tuple<string, string>("Guess", "JH"),
                new Tuple<string, string>("Guess", "QH"),
            };

            // Given
            ordersString = "Play GuessACard - SetDeck JH, QH, KH - StartGame - Guess JH - Guess QH";

            // When
            ordersReceived = new SelectedParser().ProperlyParse(ordersString);

            // Then
            for (int i = 0; i < ordersExpected.Count; i++)
            {
                Assert.AreEqual(ordersExpected[i], ordersReceived[i]);
            }

        }

        [Test]
        public void T_111_CardDeckCanHaveConfiguredRandomGenerator_First()
        {
            // Commentary
            // ---
            // There is no such random generator like one which always returns
            // the FIRST card from the CardDeck.
            // Therefore we should create such a generator.
            // It should return exactly the same sequence of cards it was given.
            // ---

            // Given, Expected
            AlwaysFirstSelector selector = new AlwaysFirstSelector();
            List<Card> expectedCards = new CreateCards().CreateCollection("9H, 10H, 9C, 10C, AD");

            List<Card> copiedList = new List<Card>(expectedCards);
            CardDeck deck = new CardDeck(selector, copiedList);

            // When
            List<Card> actualCards = new List<Card>();

            for (int i=0; i<5; i++)
            {
                actualCards.Add(deck.DrawRandomCard());
            }

            // Then
            for(int i=0; i<5; i++)
            {
                Assert.IsTrue(expectedCards[i].Colour() == actualCards[i].Colour());
                Assert.IsTrue(expectedCards[i].Rank() == actualCards[i].Rank());
            }
            
        }

        [Test]
        public void T_112_CardDeckCanHaveConfiguredRandomGenerator_Last()
        {
            // Commentary
            // ---
            // Let's play with this a bit more. Now we want an always-last generator.
            // ---

            // Given, Expected
            AlwaysLastSelector selector = new AlwaysLastSelector();
            List<Card> expectedCards = new CreateCards().CreateCollection("9H, 10H, 9C, 10C, AD");

            List<Card> copiedList = new List<Card>(expectedCards);
            CardDeck deck = new CardDeck(selector, copiedList);

            // When
            List<Card> actualCards = new List<Card>();

            for (int i = 0; i < 5; i++)
            {
                actualCards.Add(deck.DrawRandomCard());
            }

            // Then
            for (int i = 0; i < 5; i++)
            {
                Assert.IsTrue(expectedCards[4-i].Colour() == actualCards[i].Colour());
                Assert.IsTrue(expectedCards[4-i].Rank() == actualCards[i].Rank());
            }

        }

        [Test]
        public void T_113_CardDeckFactory_CanReconfigureRandomGenerator()
        {
            // Commentary
            // ---
            // We have two generators. And now we want to be able to change the CreateCardDeck in such a way
            // we are able to swap the random generator on the fly. 
            // You have to implement creator.SetCardSelector() to configure the CardDeck via CreateCardDeck.
            // ---

            // Given
            string inputCardSigils = "JS, QH, KD, AC";

            // Expected
            List<Card> expectedCards = new CreateCards().CreateCollection(inputCardSigils);

            // Given: look at this CLOSELY
            CreateCardDeck creator = new CreateCardDeck();

            creator.SetCardSelector(new AlwaysFirstSelector());
            CardDeck deckWithAlwaysFirst = creator.FromGivenCards(inputCardSigils);

            // When
            List<Card> actualFirstCards = new List<Card>();

            for (int i = 0; i < 4; i++)
            {
                actualFirstCards.Add(deckWithAlwaysFirst.DrawRandomCard());
            }

            // Then
            for (int i = 0; i < 4; i++)
            {
                Assert.IsTrue(expectedCards[i].Colour() == actualFirstCards[i].Colour());
                Assert.IsTrue(expectedCards[i].Rank() == actualFirstCards[i].Rank());
            }

            // Given again
            creator.SetCardSelector(new AlwaysLastSelector());
            CardDeck deckWithAlwaysLast = creator.FromGivenCards(inputCardSigils);

            // When
            List<Card> actualLastCards = new List<Card>();

            for (int i = 0; i < 4; i++)
            {
                actualLastCards.Add(deckWithAlwaysLast.DrawRandomCard());
            }

            // Then
            for (int i = 0; i < 4; i++)
            {
                Assert.IsTrue(expectedCards[3-i].Colour() == actualLastCards[i].Colour());
                Assert.IsTrue(expectedCards[3-i].Rank() == actualLastCards[i].Rank());
            }
        }

    }

}