using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Containers.GameRules;
using Core.Entities.GameStates;
using Core.Entities.Cards;
using Core.Entities.Decks;
using Core.Usecases.InfluenceState;

namespace Core.Usecases.GameActions
{
    public class AddQueenOfHeartsToDeck : IGameAction
    {
        public void ChangeGameState(GameState currentGameState, PlayedGameRules gameRules, string orderParams)
        {
            throw new NotImplementedException("Implement this for T202 Add Queen of Hearts");
        }

        public bool ShouldReactTo(string item1)
        {
            throw new NotImplementedException();
        }
    }
}
