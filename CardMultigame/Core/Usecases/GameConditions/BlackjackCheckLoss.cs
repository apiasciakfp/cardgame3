using Core.Entities.GameStates;
using Core.Usecases.InfluenceState;
using System;
using System.Collections.Generic;
using System.Text;

namespace Core.Usecases.GameConditions
{
    class BlackjackCheckLoss : IGameCondition
    {
        public void CheckAndUpdate(GameState currentGameState)
        {
            int currentPoints = (currentGameState["Points"] as int?).Value;
            if (currentPoints > 21)
            {
                ModifyGameState.DeclareGameToBeLost(currentGameState);
            }
        }
    }
}
