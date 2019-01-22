using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Core.Usecases.CardComparison
{
    public class CreateCardComparisonStrategy
    {
        public ICardComparisonStrategy Create(string selector)
        {
            if (selector == "strict") return new StrictCardComparisonStrategy();
            if (selector == "colour") return new ColourCardComparisonStrategy();
            if (selector == "blackred") return new BlackRedColourOnlyComparisonStrategy();
            if (selector == "rank") return new RankCardComparisonStrategy();
            else return new AlwaysFailComparisonStrategy();
        }

        public ICardComparisonStrategy None()
        {
            return new AlwaysFailComparisonStrategy();
        }
    }
}
