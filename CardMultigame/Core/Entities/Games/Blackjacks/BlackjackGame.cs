using Core.Entities.Decks;
using Core.Entities.Games.Guessing;
using Core.Entities.GameStates;
using Core.Usecases.CardComparison;
using Core.Usecases.GameActions;
using Core.Usecases.GameConditions;
using Core.Usecases.PointCalculators;
using System;
using System.Collections.Generic;
using System.Text;

namespace Core.Entities.Games.Blackjacks
{
    public class BlackjackGame : IGameImplementation
    {

        public ICardComparisonStrategy CardComparisonStrategy()
        {
            // I dislike this immensely. Would be nice to refactor.
            return new AlwaysFailComparisonStrategy();
        }

        public ICardPointCalculator CardPointCalculator()
        {
            return new DefaultBlackjackPointCalculator();
        }

        public CardDeck CardDeck()
        {
            return new CreateCardDeck().Simple9ToKWith4Colours();
        }

        public List<IGameAction> AvailableActions()
        {
            return new List<IGameAction>() { new BlackjackDrawAction(), new BlackjackPassAction() };
        }

        public List<IGameCondition> GameStopConditions()
        {
            return new List<IGameCondition>() { new BlackjackCheckLoss() };
        }

        public GameState InitialGameState()
        {
            return new GameState()
            {
                { "Points", 0 }
            };
        }

        public string Title()
        {
            return "Blackjack Game";
        }

        public List<IGameCondition> VictoryConditions()
        {
            return new List<IGameCondition>() { new BlackjackCheckWin() };
        }

        
    }
}
