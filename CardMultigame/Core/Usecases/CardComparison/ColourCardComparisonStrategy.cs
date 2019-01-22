using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Entities.Cards;

namespace Core.Usecases.CardComparison
{
    public class ColourCardComparisonStrategy : ICardComparisonStrategy
    {
        public bool AreTheSame(Card card1, Card card2)
        {
            if (card1.Colour() == card2.Colour())
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
