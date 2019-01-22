using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Entities.Cards;

namespace Core.Technical.RanGens
{
    public class AlwaysFirstSelector : ICardSelector
    {
        public Card DrawCard(List<Card> cards)
        {
            throw new NotImplementedException("Implement this for T111 Always-first selector");
        }
    }
}
