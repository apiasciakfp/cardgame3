using Core.Entities.Decks;
using Core.Entities.GameStates;
using System;

namespace Core.Usecases.InfluenceState
{
    /// <summary>
    /// STATELESS FOREVER. Queries over a Dictionary ONLY.
    /// Queries do not, ever, change the internal state at all. They are automatically safe.
    /// 
    /// This is a hint of 'Q' in CQS.
    /// </summary>
    public static class QueryGameState
    {
        public static int MaximumTurns(GameState currentState)
        {
            int? currentTurn = currentState[GameStateKeys.MaxTurns] as int?;

            if (currentTurn == null) throw new ArgumentNullException("Current turn cannot be a null");
            else return currentTurn.Value;
        }

        public static bool IsGameWon(GameState currentState)
        {
            throw new NotImplementedException("Implement this for T206 Queries Can't Change A Lot");
        }

        public static bool IsGameLost(GameState currentState)
        {
            throw new NotImplementedException("Implement this for T206 Queries Can't Change A Lot");
        }

        public static bool IsGameFinished(GameState currentState)
        {
            return IsGameWon(currentState) || IsGameLost(currentState);
        }

        public static int CurrentTurn(GameState currentState)
        {
            int? currentTurn = currentState[GameStateKeys.CurrentTurn] as int?;

            if (currentTurn == null) throw new ArgumentNullException("Current turn cannot be a null");
            else return currentTurn.Value;
        }

        public static int AmountOfCardsLeft(GameState currentState)
        {
            return ExtractCardDeck(currentState).CardsLeft();
        }

        public static string GameUndergoing(GameState currentState)
        {
            if ((bool)currentState[GameStateKeys.IsGameWon]) return "Victory";
            else if ((bool)currentState[GameStateKeys.IsGameLost]) return "Defeat";
            else return "Undergoing";
        }

        public static CardDeck ExtractCardDeck(GameState currentState)
        {
            return currentState[GameStateKeys.CardDeck] as CardDeck;
        }

    }
}
