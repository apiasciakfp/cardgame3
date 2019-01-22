using System;
using Core.Entities.Decks;

namespace Core.Entities.GameStates
{
    public class CreateGameState
    {
        public GameState WithModifications(GameState stateModifier = null, CardDeck deck = null)
        {
            CardDeck deck2 = Sanitize(deck);
            GameState stateModifier2 = Sanitize(stateModifier);

            GameState constructedState = Default();
            foreach (var kvPair in stateModifier2)
            {
                constructedState[kvPair.Key] = kvPair.Value;
            }

            constructedState[GameStateKeys.CardDeck] = deck2;
            return constructedState;
        }

        public GameState DefaultsPlusDeck(CardDeck deck)
        {
            GameState constructedState = Default();
            constructedState[GameStateKeys.CardDeck] = deck;
            return constructedState;
        }

        public GameState DefaultsWithFullDeck()
        {
            GameState constructedState = Default();
            constructedState[GameStateKeys.CardDeck] = new CreateCardDeck().Simple2ToAWith4Colours();
            return constructedState;
        }

        public GameState Default()
        {
            return new GameState()
            {
                { GameStateKeys.CardDeck, new CreateCardDeck().Empty()},
                { GameStateKeys.CurrentTurn, 0 },
                { GameStateKeys.MaxTurns, 0 },
                { GameStateKeys.IsGameLost, false },
                { GameStateKeys.IsGameWon, false }
            };
        }


        private GameState Sanitize(GameState stateModifier)
        {
            if (stateModifier == null)
                return new GameState();
            else
                return stateModifier;
        }

        private static CardDeck Sanitize(CardDeck deck)
        {
            if (deck == null)
                return new CreateCardDeck().Empty();
            else
                return deck;
        }

    }
}
