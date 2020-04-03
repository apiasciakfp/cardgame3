using Core.Entities.Cards;
using Core.Usecases.CardComparison;
using System;
using System.Collections.Generic;
using System.Text;

namespace Core._Extras.AdapterDecorator
{
    public class CardComparisonStrategyInvertingDecorator : 
        ICardComparisonStrategy
    {
        private ICardComparisonStrategy _ccStrat;

        public CardComparisonStrategyInvertingDecorator(
            ICardComparisonStrategy ccStrat)
        {
            this._ccStrat = ccStrat;
        }

        public bool AreTheSame(Card card1, Card card2)
        {
            // YES, we could have added logging, exception handling, 
            // other aspects here. But I am only inverting :-(.

            bool result = _ccStrat.AreTheSame(card1, card2);
            bool inverted = !result;
            return inverted;
        }
    }
}
