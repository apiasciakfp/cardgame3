using Core.Entities.Cards;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Core.Technical.RanGens
{
    public class RandomCardSelector : ICardSelector
    {
        Random _random = new Random(DateTime.Now.Millisecond);

        public Card DrawCard(List<Card> cards)
        {
            int index = _random.Next(0, cards.Count - 1);
            Card drawn = cards[index];
            return drawn;
        }
    }
}
