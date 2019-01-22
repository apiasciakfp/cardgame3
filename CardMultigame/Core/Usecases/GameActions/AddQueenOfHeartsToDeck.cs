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
            CardDeck deck = QueryGameState.ExtractCardDeck(currentGameState);
            deck.AddASingleCard(new Card("Q", "H"));
        }

        public bool ShouldReactTo(string item1)
        {
            throw new NotImplementedException();
        }
    }
}
