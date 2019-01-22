using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Containers.GameRules;
using Core.Entities.GameStates;

namespace Core.Usecases.GameActions
{
    public interface IGameAction
    {
        bool ShouldReactTo(string item1);
        void ChangeGameState(GameState currentGameState, PlayedGameRules gameRules, string orderParams);
    }
}
