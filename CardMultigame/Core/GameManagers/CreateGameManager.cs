using Core.Containers.GameRules;
using Core.Entities.GameStates;
using Core.GameManagers.SelectedRules;
using Core.Technical.Parsers;
using Core.Usecases.CardComparison;
using Core.Usecases.GameActions;
using Core.Usecases.GameConditions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Core.Interfaces.GameManagers
{
    public class CreateGameManager
    {
        public GameManager DefaultsWithOrders(string orderString)
        {
            List<Tuple<string, string>> orders = new SelectedParser().ProperlyParse(orderString);

            GameManagerInternalsBuilder builder = new CreateGameStructure().BuildRulesAndInitialState(orders);

            PlayedGameRules rules = builder.ConstructRuleset();
            GameState initialState = builder.ConstructGameState();

            return new GameManager(initialState, rules);
        }

        public GameManager Empty()
        {
            GameState initialState = new CreateGameState().Default();
            PlayedGameRules rules = new CreatePlayedGameRules().Empty();

            return new GameManager(initialState, rules);
        }
    }
}
