using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Entities.Decks;
using Core.Entities.GameStates;
using Core.Usecases.GameActions;
using Core.Usecases.GameConditions;
using Core.Usecases.CardComparison;

namespace Core.Containers.GameRules
{
    public class PlayedGameRules
    {
        private string _gameName;
        private List<IGameAction> _actions;
        private List<IGameCondition> _victoryConditions;
        private List<IGameCondition> _gameStopConditions;
        private ICardComparisonStrategy _cardComparator;

        public PlayedGameRules(string gameName, List<IGameAction> actions, List<IGameCondition> victories, 
            List<IGameCondition> gameStops, ICardComparisonStrategy compareCards)
        {
            _gameName = gameName;
            _actions = actions;
            _victoryConditions = victories;
            _gameStopConditions = gameStops;
            _cardComparator = compareCards;
        }

        public ICardComparisonStrategy CardComparator()
        {
            return _cardComparator;
        }

        // Usually those three would remain private.
        // But tests for patterns kind of need it.
        public List<IGameAction> GameActions() { return _actions; }
        public List<IGameCondition> VictoryConditions() { return _victoryConditions; }
        public List<IGameCondition> GameStopConditions() { return _gameStopConditions; }
        public string GameName() { return _gameName; }

        public void CheckVictoryConditions(GameState currentGameState)
        {
            foreach(IGameCondition victory in _victoryConditions)
            {
                victory.CheckAndUpdate(currentGameState);
            }
        }

        public void CheckGameStopConditions(GameState currentGameState)
        {
            foreach (IGameCondition stop in _gameStopConditions)
            {
                stop.CheckAndUpdate(currentGameState);
            }
        }

    }
}
