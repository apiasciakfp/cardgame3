using Core.Entities.Cards;
using Core.Technical.RanGens;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Core.Entities.Decks
{
    public class CreateCardDeck
    {
        private ICardSelector _selectedCardSelector = new RandomCardSelector();

        public CardDeck FromGivenCards(string cardsInDeck)
        {
            List<Card> cards = new CreateCards().CreateCollection(cardsInDeck);
            return new CardDeck(_selectedCardSelector, cards);
        }

        public CardDeck Simple9ToAWith4Colours()
        {
            List<string> ranks = new List<string>() { "9", "10", "J", "Q", "K", "A" };
            List<string> colours = new List<string>() { "S", "H", "D", "C" };

            List<Card> cards = new List<Card>();
            foreach (var rank in ranks)
            {
                foreach(var colour in colours)
                {
                    string cardPrototype = rank + colour;
                    Card card = new CreateCards().CreateSingle(cardPrototype);
                    cards.Add(card);
                }
            }

            return new CardDeck(_selectedCardSelector, cards);
        }

        public CardDeck Simple2ToAWith4Colours()
        {
            List<string> ranks = new List<string>() { "2", "3", "4", "5", "6", "7", "8",
                "9", "10", "J", "Q", "K", "A" };
            List<string> colours = new List<string>() { "S", "H", "D", "C" };

            List<Card> cards = new List<Card>();
            foreach (var rank in ranks)
            {
                foreach (var colour in colours)
                {
                    string cardPrototype = rank + colour;
                    Card card = new CreateCards().CreateSingle(cardPrototype);
                    cards.Add(card);
                }
            }

            return new CardDeck(_selectedCardSelector, cards);
        }

        public CardDeck Empty()
        {
            return new CardDeck(_selectedCardSelector, new List<Card>());
        }


        /// <summary>
        /// This is a setter method to change the default random generator
        /// </summary>
        public void SetCardSelector(ICardSelector selector)
        {
            _selectedCardSelector = selector;
        }

    }
}
