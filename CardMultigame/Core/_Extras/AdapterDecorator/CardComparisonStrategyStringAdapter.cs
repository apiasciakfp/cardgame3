using Core.Entities.Cards;
using Core.Usecases.CardComparison;
using System;
using System.Collections.Generic;
using System.Text;

namespace Core._Extras.AdapterDecorator
{
    public class CardComparisonStrategyStringAdapter
    {
        private ICardComparisonStrategy _ccStrat;

        public CardComparisonStrategyStringAdapter(ICardComparisonStrategy ccStrat)
        {
            this._ccStrat = ccStrat;
        }

        public string AreTheSame(string card1, string card2)
        {
            Card adapted1 = new CreateCards().CreateSingle(card1);
            Card adapted2 = new CreateCards().CreateSingle(card2);

            bool result = _ccStrat.AreTheSame(adapted1, adapted2);

            return result.ToString();
        }
    }
}
