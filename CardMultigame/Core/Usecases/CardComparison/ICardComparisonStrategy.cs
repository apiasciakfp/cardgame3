using Core.Entities.Cards;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Core.Usecases.CardComparison
{
    public interface ICardComparisonStrategy
    {
        bool AreTheSame(Card card1, Card card2);
    }
}
