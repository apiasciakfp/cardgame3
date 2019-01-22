using Core.Entities.Games.Guessing;
using System.Collections.Generic;
using Core.Entities.Decks;
using Core.Usecases.GameActions;
using Core.Usecases.GameConditions;
using Core.Entities.GameStates;
using Core.Usecases.CardComparison;

namespace Core.Entities.Games
{
    public class GuessACardGame : IGameImplementation
    {
        public CardDeck CardDeck()
        {
            return new CreateCardDeck().Simple9ToAWith4Colours();
        }

        public List<IGameAction> AvailableActions()
        {
            return new List<IGameAction>() { new GuessCardAction() };
        }

        public List<IGameCondition> GameStopConditions()
        {
            return new List<IGameCondition>() { new DidTurnsExpire() };
        }

        public List<IGameCondition> VictoryConditions()
        {
            return new List<IGameCondition>() { new DidGuessACard() };
        }

        public GameState InitialGameState()
        {
            return new GameState()
            {
                { GameStateKeys.MaxTurns, 5 }
            };
        }

        public string Title()
        {
            return "Guess a Card!";
        }

        public ICardComparisonStrategy CardComparisonStrategy()
        {
            return new StrictCardComparisonStrategy();
        }
    }
}
