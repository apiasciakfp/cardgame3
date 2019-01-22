using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Technical.Parsers;
using Core.Entities.GameStates;
using Core.Containers.GameRules;
using Core.Usecases.GameActions;
using Core.Usecases.InfluenceState;

namespace Core.Interfaces.GameManagers
{
    public class GameManager
    {
        GameState _currentGameState;
        PlayedGameRules _gameRules;

        public GameManager(GameState initialState, PlayedGameRules rules)
        {
            this._currentGameState = initialState;
            this._gameRules = rules;
        }

        public void ExecuteOrders(string orderString)
        {
            List<Tuple<string, string>> orders = new SelectedParser().ProperlyParse(orderString);

            foreach (Tuple<string, string> order in orders)
            {
                if (QueryGameState.IsGameFinished(_currentGameState)) return;

                foreach (IGameAction gameAction in _gameRules.GameActions())
                {
                    if (gameAction.ShouldReactTo(order.Item1))
                    {
                        gameAction.ChangeGameState(_currentGameState, _gameRules, order.Item2);

                        _gameRules.CheckVictoryConditions(_currentGameState);
                        _gameRules.CheckGameStopConditions(_currentGameState);
                    }
                }
            }

        }

        public GameState CurrentState()
        {
            return _currentGameState;
        }
    }
}
