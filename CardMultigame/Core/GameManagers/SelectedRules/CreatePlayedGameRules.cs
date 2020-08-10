using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Containers.GameRules;
using Core.Usecases.GameActions;
using Core.Usecases.GameConditions;
using Core.Usecases.CardComparison;
using Core.Usecases.PointCalculators;

namespace Core.GameManagers.SelectedRules
{
    public class CreatePlayedGameRules
    {
        private string _defaultGameName = "No game selected";
        private List<IGameAction> _defaultActions = new List<IGameAction>();
        private List<IGameCondition> _defaultVictories = new List<IGameCondition>();
        private List<IGameCondition> _defaultGameStops = new List<IGameCondition>();
        private ICardComparisonStrategy _defaultCardComparators = new CreateCardComparisonStrategy().None();
        private ICardPointCalculator _defaultPointCalculators = new DefaultBlackjackPointCalculator();


        public PlayedGameRules Empty()
        {
            return new PlayedGameRules(_defaultGameName, _defaultActions, _defaultVictories, _defaultGameStops, _defaultCardComparators, _defaultPointCalculators);
        }


        public PlayedGameRules WithModifications(string gameName, List<IGameAction> actions, List<IGameCondition> victories, 
            List<IGameCondition> gameStops, ICardComparisonStrategy compareCards, ICardPointCalculator calculatePoints)
        {
            var selectedName = _defaultGameName;
            var selectedActions = _defaultActions;
            var selectedVictories = _defaultVictories;
            var selectedGameStops = _defaultGameStops;
            var selectedCardComparators = _defaultCardComparators;
            var selectedPointCalculator = _defaultPointCalculators;

            if (gameName != null)
                selectedName = gameName;

            if (actions != null)
                selectedActions = actions;

            if (victories != null)
                selectedVictories = victories;

            if (gameStops != null)
                selectedGameStops = gameStops;

            if (compareCards != null)
                selectedCardComparators = compareCards;

            if (calculatePoints != null)
                selectedPointCalculator = calculatePoints;

            return new PlayedGameRules(selectedName, selectedActions, selectedVictories, selectedGameStops, selectedCardComparators, selectedPointCalculator);

        }
    }
}
