using Core._Extras.AdapterDecorator;
using Core._Extras.Visitor;
using Core.Entities.Cards;
using Core.Usecases.CardComparison;
using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Text;

namespace ExtrasTests
{
    public class TestAdapterDecorator
    {
        [Test]
        public void AdapterChangesInterfaces()
        {
            // Given

            string card1 = "2H";
            string card2 = "2D";

            var strictStrat = new CreateCardComparisonStrategy().Create("strict");
            var blackredStrat = new CreateCardComparisonStrategy().Create("blackred");

            // building ADAPTERS:

            var strictAdapter = new CardComparisonStrategyStringAdapter(strictStrat);
            var blackredAdapter = new CardComparisonStrategyStringAdapter(blackredStrat);

            // results

            string resultStrict = strictAdapter.AreTheSame(card1, card2);
            string resultBlackred = blackredAdapter.AreTheSame(card1, card2);

            // testing if they work:

            Assert.IsTrue(resultStrict == "False");
            Assert.IsTrue(resultBlackred == "True");
        }

        [Test]
        public void DecoratorChangesBehavior()
        {
            // Given

            var card1 = new CreateCards().CreateSingle("2H");
            var card2 = new CreateCards().CreateSingle("2D");

            ICardComparisonStrategy strictStrat;

            // no decorator:

            strictStrat = 
                new CreateCardComparisonStrategy().Create("strict");

            bool result = strictStrat.AreTheSame(card1, card2);
            Assert.IsTrue(result == false);

            // one inverting decorator:

            strictStrat = new CardComparisonStrategyInvertingDecorator(strictStrat);

            bool invertedResult = strictStrat.AreTheSame(card1, card2);
            Assert.IsTrue(invertedResult == true);

            // two inverting decorator:

            strictStrat = new CardComparisonStrategyInvertingDecorator(strictStrat);

            bool doubleInvertedResult = strictStrat.AreTheSame(card1, card2);
            Assert.IsTrue(doubleInvertedResult == false);

        }
    }
}
