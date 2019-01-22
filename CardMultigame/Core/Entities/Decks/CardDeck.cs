using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Entities.Cards;
using Core.Technical.RanGens;

namespace Core.Entities.Decks
{
    public class CardDeck
    {
        ICardSelector _selector = new RandomCardSelector();
        List<Card> _cards = new List<Card>();

        public CardDeck(ICardSelector selector, List<Card> cards)
        {
            this._selector = selector;
            this._cards = cards;
        }

        public List<Card> AllCards() { return _cards; }
        public int CardsLeft() { return _cards.Count(); }


        public Card DrawRandomCard()
        {
            Card drawn = _selector.DrawCard(_cards);
            _cards.Remove(drawn);

            return drawn;
        }

        public Card DrawLastAddedCard()
        {
            Card drawn = _cards[_cards.Count - 1];
            _cards.Remove(drawn);

            return drawn;
        }

        public void AddASingleCard(Card card)
        {
            _cards.Add(card);
        }

    }
}
