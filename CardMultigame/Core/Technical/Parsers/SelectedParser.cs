using Core.Technical.Parsers.ParseStrategies;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Core.Technical.Parsers
{
    public class SelectedParser
    {
        List<IParseStrategy> _parseStrategies;

        public SelectedParser()
        {
            _parseStrategies = RegisterPossibleStrategies();
        }

        public List<Tuple<string, string>> ProperlyParse(string orderString)
        {
            IParseStrategy selectedStrategy = SelectAppropriateStrategy(orderString);

            if (selectedStrategy == null) throw new ArgumentException("Order string is wrong or appropriate parsing Strategy is not registered");

            List<Tuple<string, string>> result = new PerformParsing(selectedStrategy).ExecuteOn(orderString);
            return result;
        }


        private IParseStrategy SelectAppropriateStrategy(string orderString)
        {
            int lastPostition = int.MaxValue;
            IParseStrategy selectedStrategy = null;
            foreach (var strategy in _parseStrategies)
            {
                string potential = strategy.Separator();

                int currentPosition = orderString.IndexOf(potential);
                if (currentPosition > 0 && currentPosition < lastPostition)
                {
                    selectedStrategy = strategy;
                    lastPostition = currentPosition;
                }
            }

            return selectedStrategy;
        }

        private List<IParseStrategy> RegisterPossibleStrategies()
        {
            // Some changes here, perhaps? For T110 - parsers

            var registeredStrategies = new List<IParseStrategy>()
            {
                new CommaParseStrategy(),
                new SemicolonParseStrategy()
            };

            return registeredStrategies;
        }

    }
}
