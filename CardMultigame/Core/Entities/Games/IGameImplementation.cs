using Core.Entities.Decks;
using Core.Usecases.GameActions;
using Core.Usecases.GameConditions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Entities.GameStates;
using Core.Usecases.CardComparison;

namespace Core.Entities.Games.Guessing
{
    public interface IGameImplementation
    {
        string Title();
        CardDeck CardDeck();
        List<IGameAction> AvailableActions();
        List<IGameCondition> VictoryConditions();
        List<IGameCondition> GameStopConditions();
        GameState InitialGameState();
        ICardComparisonStrategy CardComparisonStrategy();
    }
}
