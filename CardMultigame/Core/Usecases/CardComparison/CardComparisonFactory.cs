using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Core.Usecases.CardComparison
{
    public class CardComparisonFactory
    {
        public ICardComparisonStrategy Create(string selector)
        {
            throw new NotImplementedException("Test 105");
        }

        public ICardComparisonStrategy None()
        {
            throw new NotImplementedException("Test 107");
        }
    }
}
