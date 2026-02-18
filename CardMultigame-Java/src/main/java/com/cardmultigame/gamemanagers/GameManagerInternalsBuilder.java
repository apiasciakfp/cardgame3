package com.cardmultigame.gamemanagers;

import com.cardmultigame.entities.decks.CardDeck;
import com.cardmultigame.entities.gamestates.CreateGameState;
import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.entities.gamestates.GameStateKeys;
import com.cardmultigame.gamemanagers.selectedrules.CreatePlayedGameRules;
import com.cardmultigame.gamemanagers.selectedrules.PlayedGameRules;
import com.cardmultigame.usecases.cardcomparison.ICardComparisonStrategy;
import com.cardmultigame.usecases.gameactions.IGameAction;
import com.cardmultigame.usecases.gameconditions.IGameCondition;
import java.util.List;

public class GameManagerInternalsBuilder {
    private String gameName;
    private CardDeck deck;
    private List<IGameAction> actions;
    private List<IGameCondition> victories;
    private List<IGameCondition> gameStops;
    private GameState initialGameState;
    private ICardComparisonStrategy compareCards;

    public PlayedGameRules constructRuleset() {
        return new CreatePlayedGameRules().withModifications(gameName, actions, victories, gameStops, compareCards);
    }

    public GameState constructGameState() {
        return new CreateGameState().withModifications(initialGameState, deck);
    }

    public void setName(String name) { this.gameName = name; }
    public void setAvailableActions(List<IGameAction> actions) { this.actions = actions; }
    public void setVictoryConditions(List<IGameCondition> victories) { this.victories = victories; }
    public void setGameStopConditions(List<IGameCondition> gameStops) { this.gameStops = gameStops; }
    public void setDeck(CardDeck cardDeck) { this.deck = cardDeck; }
    public void setInitialGameState(GameState gameState) { this.initialGameState = gameState; }
    public void setMaxTurns(int maxTurns) { this.initialGameState.put(GameStateKeys.MaxTurns, maxTurns); }

    public CardDeck getCardDeck() { return deck; }

    public void setCardComparisonStrategy(ICardComparisonStrategy selected) { this.compareCards = selected; }
}
