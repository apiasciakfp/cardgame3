using Core.Entities.GameStates;

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
            currentGameState[GameStateKeys.IsGameLost] = true;
        }

        public static void DeclareGameToBeWon(GameState currentGameState)
        {
            currentGameState[GameStateKeys.IsGameWon] = true;
        }


    }
}
