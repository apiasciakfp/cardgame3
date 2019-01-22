using Core.Entities.GameStates;
using System;

namespace Core.Usecases.InfluenceState
{
    /// <summary>
    /// STATELESS FOREVER. Commands (functions) over a Dictionary ONLY.
    /// Commands change the internal state, they do not retrieve anything.
    /// 
    /// This is a hint of 'C' in CQS.
    /// </summary>
    public static class ModifyGameState
    {
        public static void AddTurn(GameState currentGameState)
        {
            int? currentTurn = currentGameState[GameStateKeys.CurrentTurn] as int?;
            currentGameState[GameStateKeys.CurrentTurn] = (currentTurn + 1) as int?;
        }

        public static void DeclareGameToBeLost(GameState currentGameState)
        {
            throw new NotImplementedException("Implement this for T207 ModifyTheGameState");
        }

        public static void DeclareGameToBeWon(GameState currentGameState)
        {
            throw new NotImplementedException("Implement this for T207 ModifyTheGameState");
        }


    }
}
