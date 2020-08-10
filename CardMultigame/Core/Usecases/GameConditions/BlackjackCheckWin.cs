using Core.Entities.GameStates;
using Core.Usecases.InfluenceState;
using System;
using System.Collections.Generic;
using System.Text;

namespace Core.Usecases.GameConditions
{
    class BlackjackCheckWin : IGameCondition
    {
        public void CheckAndUpdate(GameState currentGameState)
        {
            if(currentGameState["NextCardPoints"] != null)
            {
                int currentPoints = (currentGameState["Points"] as int?).Value;
                int nextPoints = (currentGameState["NextCardPoints"] as int?).Value;

                if (currentPoints + nextPoints >= 21)
                {
                    ModifyGameState.DeclareGameToBeWon(currentGameState);
                }   
                else
                {
                    ModifyGameState.DeclareGameToBeLost(currentGameState);
                }    
            }
        }
    }
}
