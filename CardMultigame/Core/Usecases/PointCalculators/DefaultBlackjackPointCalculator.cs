using Core.Entities.Cards;
using System;
using System.Collections.Generic;
using System.Text;

namespace Core.Usecases.PointCalculators
{
    public class DefaultBlackjackPointCalculator : ICardPointCalculator
    {
        Dictionary<string, int> _cardMapper;

        public DefaultBlackjackPointCalculator()
        {
            _cardMapper = new Dictionary<string, int>()
            {
                { "K", 6 },
                { "Q", 5 },
                { "J", 4 },
                { "10", 3 },
                { "9", 2 },
            };
        }

        public int CalculatePoints(Card actuallyDrawnCard)
        {
            return _cardMapper[actuallyDrawnCard.Rank];
        }
    }
}
