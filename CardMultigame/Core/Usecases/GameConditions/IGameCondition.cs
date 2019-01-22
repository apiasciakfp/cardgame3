using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Entities.GameStates;

namespace Core.Usecases.GameConditions
{
    public interface IGameCondition
    {
        void CheckAndUpdate(GameState currentGameState);
    }
}
