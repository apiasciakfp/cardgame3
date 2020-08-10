using Core.Containers.GameRules;
using Core.Entities.Cards;
using Core.Entities.Decks;
using Core.Entities.GameStates;
using Core.Usecases.InfluenceState;
using Core.Usecases.PointCalculators;
using System;
using System.Collections.Generic;
using System.Text;

namespace Core.Usecases.GameActions
{
    class BlackjackDrawAction : IGameAction
    {
        string _identifier = "Draw";

        public void ChangeGameState(GameState currentGameState, PlayedGameRules gameRules, string orderParams)
        {
            // Draw a card
            CardDeck deck = QueryGameState.ExtractCardDeck(currentGameState);
            Card actuallyDrawnCard = deck.DrawRandomCard();

            // Calculate score
            ICardPointCalculator calc = gameRules.CardPointCalculator();
            int cardPoints = calc.CalculatePoints(actuallyDrawnCard);

            // Append the score to current score
            int currentScore = (currentGameState["Points"] as int?).Value;
            currentGameState["Points"] = currentScore + cardPoints;
        }

        public bool ShouldReactTo(string orderName)
        {
            return _identifier.ToLower() == orderName.ToLower();
        }
    }
}
