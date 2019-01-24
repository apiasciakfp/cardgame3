using System.Collections.Generic;
using Core.Entities.Decks;
using Core.Usecases.GameActions;
using Core.Usecases.GameConditions;
using Core.Entities.GameStates;
using Core.Usecases.CardComparison;
using Core.GameManagers.SelectedRules;

namespace Core.Containers.GameRules
{
    public class GameManagerInternalsBuilder
    {
        private string _gameName;
        private CardDeck _deck;
        private List<IGameAction> _actions;
        private List<IGameCondition> _victories;
        private List<IGameCondition> _gameStops;
        private GameState _initialGameState;

        //This one is specific to Guessing Game.
        private ICardComparisonStrategy _compareCards;


        public PlayedGameRules ConstructRuleset()
        {
            return new PlayedGameRulesFactory().WithModifications(_gameName, _actions, _victories, _gameStops, _compareCards);
        }
        
        public GameState ConstructGameState()
        {
            return new GameStateFactory().WithModifications(_initialGameState, _deck);
        }


        public void SetName(string name) { _gameName = name; }
        public void SetAvailableActions(List<IGameAction> actions) { _actions = actions; }
        public void SetVictoryConditions(List<IGameCondition> victories) { _victories = victories; }
        public void SetGameStopConditions(List<IGameCondition> gameStops) { _gameStops = gameStops; }
        public void SetDeck(CardDeck cardDeck) { _deck = cardDeck; }
        public void SetInitialGameState(GameState gameState) { _initialGameState = gameState; }
        public void SetMaxTurns(int maxTurns) { _initialGameState[GameStateKeys.MaxTurns] = maxTurns; }

        public CardDeck GetCardDeck() => _deck;


        // Specific to Guessing Game. Should be more general, like with InternalState
        public void SetCardComparisonStrategy(ICardComparisonStrategy selected) { _compareCards = selected; }

    }
}
