using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Entities.GameStates;
using Core.Entities.Cards;
using Core.Containers.GameRules;
using Core.Usecases.CardComparison;
using Core.Usecases.InfluenceState;
using Core.Entities.Decks;

namespace Core.Usecases.GameActions
{
    public class GuessCardAction : IGameAction
    {
        string _identifier = "Guess";

        public void ChangeGameState(GameState currentGameState, PlayedGameRules rules, string orderParams)
        {
            Card candidate = new CreateCards().CreateSingle(orderParams);

            CardDeck deck = QueryGameState.ExtractCardDeck(currentGameState);
            Card actuallyDrawnCard = deck.DrawRandomCard();

            ICardComparisonStrategy comparator = rules.CardComparator();

            bool areTheSame = comparator.AreTheSame(candidate, actuallyDrawnCard);

            if(areTheSame) currentGameState[_identifier] = true;
            else currentGameState[_identifier] = false;

            ModifyGameState.AddTurn(currentGameState);
        }

        public bool ShouldReactTo(string orderName)
        {
            return _identifier.ToLower() == orderName.ToLower();
        }
    }
}
