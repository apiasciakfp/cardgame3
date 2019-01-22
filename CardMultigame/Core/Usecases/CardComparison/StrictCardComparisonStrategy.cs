using Core.Entities.Cards;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Core.Usecases.CardComparison
{
    public class StrictCardComparisonStrategy : ICardComparisonStrategy
    {
        public bool AreTheSame(Card card1, Card card2)
        {
            if ((card1.Rank() == card2.Rank()) && (card1.Colour() == card2.Colour()))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
