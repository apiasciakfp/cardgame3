using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Core.Usecases.GameActions
{
    public class CreateGameActions
    {
        public List<IGameAction> HavingOrders(string actionsToPerform)
        {
            var tokens = actionsToPerform.Split();

            List<IGameAction> actions = new List<IGameAction>();
            foreach (string token in tokens)
            {
                var sanitized = token.Trim(',');

                if (sanitized == "drawSingleCard") actions.Add(new DrawSingleCardAction());
                if (sanitized == "addQH") actions.Add(new AddQueenOfHeartsToDeck());
                if (sanitized == "add10cOrDraw") actions.Add(new Add10COrDrawACard());

            }

            return actions;
        }
    }
}
