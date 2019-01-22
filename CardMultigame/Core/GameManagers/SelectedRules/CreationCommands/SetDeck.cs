using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Usecases.GameActions;
using Core.Technical.Parsers;
using Core.Entities.Decks;

namespace Core.Containers.GameRules.CreationCommands
{
    public class SetDeck : ICreateGameRulesCommand
    {
        private string _identifier = "SetDeck";

        public void ChangeGameRuleset(GameManagerInternalsBuilder builder, string parameters)
        {
            CardDeck deck = new CreateCardDeck().FromGivenCards(parameters);
            builder.SetDeck(deck);
        }

        public bool ShouldReactTo(string outerCommandName)
        {
            return _identifier.ToLower() == outerCommandName.ToLower();
        }
    }
}
