using Core.Containers.GameRules.CreationCommands;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Containers.GameRules;

namespace Core.Containers.GameManagers.Rules.CreationCommands
{
    public class SetMaxTurns : ICreateGameRulesCommand
    {
        private string _identifier = "SetMaxTurns";

        public void ChangeGameRuleset(GameManagerInternalsBuilder builder, string parameters)
        {
            bool wasSuccessful = int.TryParse(parameters, out int maxTurns);
            if(wasSuccessful)
            {
                builder.SetMaxTurns(maxTurns);
            }
            
        }

        public bool ShouldReactTo(string outerCommandName)
        {
            return _identifier.ToLower() == outerCommandName.ToLower();
        }
    }
}
