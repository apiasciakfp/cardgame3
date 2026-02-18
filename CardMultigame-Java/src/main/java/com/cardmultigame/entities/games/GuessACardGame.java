package com.cardmultigame.entities.games;

import com.cardmultigame.entities.decks.CardDeck;
import com.cardmultigame.entities.decks.CreateCardDeck;
import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.entities.gamestates.GameStateKeys;
import com.cardmultigame.usecases.cardcomparison.ICardComparisonStrategy;
import com.cardmultigame.usecases.cardcomparison.StrictCardComparisonStrategy;
import com.cardmultigame.usecases.gameactions.GuessCardAction;
import com.cardmultigame.usecases.gameactions.IGameAction;
import com.cardmultigame.usecases.gameconditions.DidGuessACard;
import com.cardmultigame.usecases.gameconditions.DidTurnsExpire;
import com.cardmultigame.usecases.gameconditions.IGameCondition;
import java.util.List;

public class GuessACardGame implements IGameImplementation {

    @Override
    public CardDeck cardDeck() {
        return new CreateCardDeck().simple9ToAWith4Colours();
    }

    @Override
    public List<IGameAction> availableActions() {
        return List.of(new GuessCardAction());
    }

    @Override
    public List<IGameCondition> gameStopConditions() {
        return List.of(new DidTurnsExpire());
    }

    @Override
    public List<IGameCondition> victoryConditions() {
        return List.of(new DidGuessACard());
    }

    @Override
    public GameState initialGameState() {
        GameState state = new GameState();
        state.put(GameStateKeys.MaxTurns, 5);
        return state;
    }

    @Override
    public String title() {
        return "Guess a Card!";
    }

    @Override
    public ICardComparisonStrategy cardComparisonStrategy() {
        return new StrictCardComparisonStrategy();
    }
}
