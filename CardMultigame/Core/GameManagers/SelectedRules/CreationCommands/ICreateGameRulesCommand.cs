using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Usecases.GameActions;

namespace Core.Containers.GameRules.CreationCommands
{
    public interface ICreateGameRulesCommand
    {
        bool ShouldReactTo(string outerCommandName);
        void ChangeGameRuleset(GameManagerInternalsBuilder builder, string parameters);
    }
}
