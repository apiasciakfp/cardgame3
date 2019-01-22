using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Core.Entities.GameStates
{
    public static class GameStateKeys
    {
        public const string CurrentTurn = "CurrentTurnNumber";
        public const string MaxTurns = "MaximumTurns";
        public const string IsGameWon = "IsGameFinishedWithVictory";
        public const string IsGameLost = "IsGameFinishedWithDefeat";
        public const string CardDeck = "CardDeck";
    }
}
