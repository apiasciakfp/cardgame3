using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Entities.Cards;

namespace Core.Usecases.CardComparison
{
    public class BlackRedColourOnlyComparisonStrategy : ICardComparisonStrategy
    {
        public bool AreTheSame(Card card1, Card card2)
        {
            Dictionary<string, string> colourMap = new Dictionary<string, string>()
            {
                {"H", "red"},
                {"D", "red" },
                {"C", "black" },
                {"S", "black" }
            };

            string card1Colour = colourMap[card1.Colour()];
            string card2Colour = colourMap[card2.Colour()];

            if (card1Colour == card2Colour)
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
