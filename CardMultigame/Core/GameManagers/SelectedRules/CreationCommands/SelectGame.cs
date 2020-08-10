using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Usecases.GameActions;
using Core.Entities.Games.Guessing;
using Core.Entities.Games;
using Core.Entities.Games.Blackjacks;

namespace Core.Containers.GameRules.CreationCommands
{
    public class SelectGame : ICreateGameRulesCommand
    {
        private string _identifier = "Play";

        public void ChangeGameRuleset(GameManagerInternalsBuilder builder, string parameters)
        {
            IGameImplementation gameImpl = SelectGameImplementation(parameters);

            builder.SetName(gameImpl.Title());
            builder.SetDeck(gameImpl.CardDeck());
            builder.SetAvailableActions(gameImpl.AvailableActions());
            builder.SetVictoryConditions(gameImpl.VictoryConditions());
            builder.SetGameStopConditions(gameImpl.GameStopConditions());
            builder.SetInitialGameState(gameImpl.InitialGameState());
            builder.SetCardComparisonStrategy(gameImpl.CardComparisonStrategy());
            builder.SetCardPointCalculator(gameImpl.CardPointCalculator());
        }

        public bool ShouldReactTo(string outerCommandName)
        {
            return _identifier.ToLower() == outerCommandName.ToLower();
        }


        private static IGameImplementation SelectGameImplementation(string parameters)
        {
            IGameImplementation gameImpl = null;
            if (parameters.ToLower() == "GuessACard".ToLower())
            {
                gameImpl = new GuessACardGame();
            }
            if (parameters.ToLower() == "Blackjack".ToLower())
            {
                gameImpl = new BlackjackGame();
            }

            if (gameImpl == null) throw new ArgumentException("Either the game is not registered in factory or game identifier has a typo. Got: " + parameters);

            return gameImpl;
        }

    }
}
