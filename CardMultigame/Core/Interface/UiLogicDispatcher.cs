using Core.Entities.GameStates;
using Core.Interfaces.GameManagers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Core.Interface
{
    public class UiLogicDispatcher
    {
        GameManager _gameManager;

        public UiLogicDispatcher()
        {
            _gameManager = new CreateGameManager().Empty();
        }

        public void DoStuff(string orders)
        {
            _gameManager.ExecuteOrders(orders);
        }

        public void SetupGame(string orders)
        {
            _gameManager = new CreateGameManager().DefaultsWithOrders(orders);
        }

        public string DisplayCurrentState()
        {
            GameState currentState = _gameManager.CurrentState();
            return string.Join(";"+ Environment.NewLine, currentState);
        }
    }
}
