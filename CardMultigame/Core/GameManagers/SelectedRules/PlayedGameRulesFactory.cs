using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Containers.GameRules;
using Core.Usecases.GameActions;
using Core.Usecases.GameConditions;
using Core.Usecases.CardComparison;

namespace Core.GameManagers.SelectedRules
{
    public class PlayedGameRulesFactory
    {
        private string _defaultGameName = "No game selected";
        private List<IGameAction> _defaultActions = new List<IGameAction>();
        private List<IGameCondition> _defaultVictories = new List<IGameCondition>();
        private List<IGameCondition> _defaultGameStops = new List<IGameCondition>();
        private ICardComparisonStrategy _defaultCardComparators = new CardComparisonFactory().None();


        public PlayedGameRules Empty()
        {
            return new PlayedGameRules(_defaultGameName, _defaultActions, _defaultVictories, _defaultGameStops, _defaultCardComparators);
        }


        public PlayedGameRules WithModifications(string gameName, List<IGameAction> actions, List<IGameCondition> victories, 
            List<IGameCondition> gameStops, ICardComparisonStrategy compareCards)
        {
            // You have to make changes to this method: T213 Factory + NullObject'

            var selectedActions = _defaultActions;
            var selectedVictories = _defaultVictories;
            var selectedGameStops = _defaultGameStops;
            var selectedCardComparators = _defaultCardComparators;

            if (actions != null)
                selectedActions = actions;

            if (victories != null)
                selectedVictories = victories;

            if (gameStops != null)
                selectedGameStops = gameStops;

            if (compareCards != null)
                selectedCardComparators = compareCards;

            return new PlayedGameRules(string.Empty, selectedActions, selectedVictories, selectedGameStops, selectedCardComparators);

        }
    }
}
