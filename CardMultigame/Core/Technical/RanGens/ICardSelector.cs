using Core.Entities.Cards;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Core.Technical.RanGens
{
    public interface ICardSelector
    {
        Card DrawCard(List<Card> cards);
    }
}
