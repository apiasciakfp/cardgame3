using Core.Containers.GameRules.CreationCommands;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Containers.GameRules;
using Core.Entities.Decks;
using Core.Entities.Cards;
using Core.Usecases.CardComparison;

namespace Core.Containers.GameManagers.Rules.CreationCommands
{
    public class GameVariant : ICreateGameRulesCommand
    {
        private string _identifier = "GameVariant";

        public void ChangeGameRuleset(GameManagerInternalsBuilder builder, string parameters)
        {
            // First, the comparator
            builder.SetCardComparisonStrategy(new BlackRedColourOnlyComparisonStrategy());
        }

        public bool ShouldReactTo(string outerCommandName)
        {
            return _identifier.ToLower() == outerCommandName.ToLower();
        }
    }
}
