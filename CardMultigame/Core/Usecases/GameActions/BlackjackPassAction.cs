using Core.Containers.GameRules;
using Core.Entities.Cards;
using Core.Entities.Decks;
using Core.Entities.GameStates;
using Core.Usecases.InfluenceState;
using System;
using System.Collections.Generic;
using System.Text;

namespace Core.Usecases.GameActions
{
    class BlackjackPassAction : IGameAction
    {
        string _identifier = "Pass";

        public void ChangeGameState(GameState currentGameState, PlayedGameRules gameRules, string orderParams)
        {
            // Get current amount of points
            int currentScore = (currentGameState["Points"] as int?).Value;

            // Draw next card
            CardDeck deck = QueryGameState.ExtractCardDeck(currentGameState);
            Card nextDrawnCard = deck.DrawRandomCard();

            // Calculate points of next card
            int nextCardPoints = gameRules.CardPointCalculator().CalculatePoints(nextDrawnCard);

            // Put the next card points to GameState
            currentGameState["NextCardPoints"] = nextCardPoints;
        }

        public bool ShouldReactTo(string orderName)
        {
            return _identifier.ToLower() == orderName.ToLower();
        }
    }
}
