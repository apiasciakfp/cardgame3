using Core.Containers.GameManagers.Rules.CreationCommands;
using Core.Containers.GameRules.CreationCommands;
using Core.Usecases.GameActions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Core.Containers.GameRules
{
    public class GameStructureFactory
    {
        List<ICreateGameRulesCommand> _commands; 

        public GameStructureFactory()
        {
            _commands = RegisterAvailableCreationCommands();
        }
        

        public GameManagerInternalsBuilder BuildRulesAndInitialState(List<Tuple<string, string>> orders)
        {
            GameManagerInternalsBuilder builder = new GameManagerInternalsBuilder();
            foreach (var order in orders)
            {
                foreach (var orderUser in _commands)
                {
                    if(orderUser.ShouldReactTo(order.Item1))
                    {
                        orderUser.ChangeGameRuleset(builder, order.Item2);
                    }
                }
            }

            return builder;
        }


        private List<ICreateGameRulesCommand> RegisterAvailableCreationCommands()
        {
            return new List<ICreateGameRulesCommand>() { new SelectGame(), new SetDeck(), new SetMaxTurns(),
                new GameVariant() };
        }
    }
}
