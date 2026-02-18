package com.cardmultigame;

import com.cardmultigame.entities.cards.Card;
import com.cardmultigame.entities.decks.CardDeck;
import com.cardmultigame.entities.decks.CreateCardDeck;
import com.cardmultigame.entities.gamestates.CreateGameState;
import com.cardmultigame.entities.gamestates.GameState;
import com.cardmultigame.entities.gamestates.GameStateKeys;
import com.cardmultigame.gamemanagers.selectedrules.CreatePlayedGameRules;
import com.cardmultigame.gamemanagers.selectedrules.PlayedGameRules;
import com.cardmultigame.entities.games.GuessACardGame;
import com.cardmultigame.gamemanagers.GameManagerInternalsBuilder;
import com.cardmultigame.gamemanagers.selectedrules.creationcommands.*;
import com.cardmultigame.usecases.cardcomparison.AlwaysFailComparisonStrategy;
import com.cardmultigame.usecases.cardcomparison.BlackRedColourOnlyComparisonStrategy;
import com.cardmultigame.usecases.cardcomparison.StrictCardComparisonStrategy;
import com.cardmultigame.usecases.gameactions.*;
import com.cardmultigame.usecases.gameconditions.*;
import com.cardmultigame.usecases.influencestate.ModifyGameState;
import com.cardmultigame.usecases.influencestate.QueryGameState;
import org.junit.jupiter.api.Test;
import java.util.List;
import static org.assertj.core.api.Assertions.assertThat;

class Batch200Test {

    @Test
    void t201_gentleIntroductionToCommand() {
        // Tutorial: how to extract the CardDeck from the GameState
        GameState tutorialState = new CreateGameState().defaultsWithFullDeck();
        CardDeck tutorialDeck = QueryGameState.extractCardDeck(tutorialState);
        tutorialDeck.drawRandomCard();

        // Given
        CardDeck deck = new CreateCardDeck().fromGivenCards("2H, 3H, 4H");
        GameState gameState = new CreateGameState().defaultsPlusDeck(deck);

        // Expected:
        assertThat(QueryGameState.amountOfCardsLeft(gameState) == 3).isTrue();
        int amountOfCardsAfterDrawingOne = QueryGameState.amountOfCardsLeft(gameState) - 1;

        // When
        new DrawSingleCardAction().changeGameState(gameState, null, null);

        // Then
        assertThat(QueryGameState.amountOfCardsLeft(gameState) == amountOfCardsAfterDrawingOne).isTrue();
    }

    @Test
    void t202_addSome_QH_intoTheCardDeck() {
        // Given
        CardDeck deck = new CreateCardDeck().fromGivenCards("2H, 3H, 4H");
        GameState gameState = new CreateGameState().defaultsPlusDeck(deck);

        List<IGameAction> actions = List.of(
            new AddQueenOfHeartsToDeck(),
            new AddQueenOfHeartsToDeck(),
            new AddQueenOfHeartsToDeck(),
            new AddQueenOfHeartsToDeck(),
            new AddQueenOfHeartsToDeck()
        );

        // Expected:
        assertThat(QueryGameState.amountOfCardsLeft(gameState) == 3).isTrue();
        int amountOfCardsAfterDrawingOne = QueryGameState.amountOfCardsLeft(gameState) + actions.size();

        // When
        for (IGameAction action : actions) {
            action.changeGameState(gameState, null, null);
        }

        // Then
        assertThat(QueryGameState.amountOfCardsLeft(gameState) == amountOfCardsAfterDrawingOne).isTrue();

        CardDeck retrievedDeck = QueryGameState.extractCardDeck(gameState);

        for (int i = 0; i < 5; i++) {
            Card card = retrievedDeck.drawLastAddedCard();
            assertThat(card.rank().equals("Q")).isTrue();
            assertThat(card.colour().equals("H")).isTrue();
        }
    }

    @Test
    void t203_chainSomeCommands() {
        // Given
        CardDeck deck = new CreateCardDeck().fromGivenCards("2H, 3H, 4H");
        GameState gameState = new CreateGameState().defaultsPlusDeck(deck);

        List<IGameAction> actions = List.of(
            new DrawSingleCardAction(),
            new DrawSingleCardAction(),
            new DrawSingleCardAction(),     // now it should be empty
            new AddQueenOfHeartsToDeck(),
            new AddQueenOfHeartsToDeck(),
            new Add10COrDrawACard(),        // should add +1 card, because even
            new Add10COrDrawACard()         // should draw a card, because odd
        );

        // Expected:
        assertThat(QueryGameState.amountOfCardsLeft(gameState) == 3).isTrue();
        int amountOfCardsAfterDrawingOne = 2;

        // When
        for (IGameAction action : actions) {
            action.changeGameState(gameState, null, null);
        }

        // Then
        assertThat(QueryGameState.amountOfCardsLeft(gameState) == amountOfCardsAfterDrawingOne).isTrue();
    }

    @Test
    void t204_factorizeMe() {
        // Given
        CardDeck deck = new CreateCardDeck().fromGivenCards("2H, 3H, 4H");
        GameState gameState = new CreateGameState().defaultsPlusDeck(deck);

        String actionsToPerform = "drawSingleCard, drawSingleCard, drawSingleCard, addQH, addQH, " +
            "add10cOrDraw, add10cOrDraw";
        List<IGameAction> actions = new CreateGameActions().havingOrders(actionsToPerform);

        // Expected:
        assertThat(QueryGameState.amountOfCardsLeft(gameState) == 3).isTrue();
        int amountOfCardsAfterDrawingOne = 2;

        // When
        for (IGameAction action : actions) {
            action.changeGameState(gameState, null, null);
        }

        // Then
        assertThat(QueryGameState.amountOfCardsLeft(gameState) == amountOfCardsAfterDrawingOne).isTrue();
    }

    @Test
    void t205_commandsCanCommunicateViaContext() {
        // Tutorial
        GameState tutorialState = new CreateGameState().defaultState();
        assertThat(tutorialState.get("SpecificKey") == null).isTrue();
        tutorialState.put("SpecificKey", "Capybara");
        assertThat(((String) tutorialState.get("SpecificKey")).equals("Capybara")).isTrue();

        // Given
        CardDeck deck = new CreateCardDeck().fromGivenCards("2H, 3H, 4H");
        GameState gameState = new CreateGameState().defaultsPlusDeck(deck);

        String actionsToPerform = "drawSingleCard, drawSingleCard, drawSingleCard";
        List<IGameAction> actions = new CreateGameActions().havingOrders(actionsToPerform);

        // Expected:
        assertThat(QueryGameState.amountOfCardsLeft(gameState) == 3).isTrue();

        // When
        for (IGameAction action : actions) {
            action.changeGameState(gameState, null, null);
        }

        // Then
        assertThat((Boolean) gameState.get("Guess") == true).isTrue();
    }

    @Test
    void t206_queryGameState_cannotChangeAThing() {
        // Given
        GameState gameState = new CreateGameState().defaultState();
        gameState.put(GameStateKeys.IsGameWon, false);
        gameState.put(GameStateKeys.IsGameLost, false);

        // When
        // Then
        assertThat(QueryGameState.isGameWon(gameState) == false).isTrue();
        assertThat(QueryGameState.isGameLost(gameState) == false).isTrue();
    }

    @Test
    void t207_modifyGameState_canChangeQuiteALot() {
        // Given
        GameState gameState = new CreateGameState().defaultState();
        gameState.put(GameStateKeys.IsGameWon, false);
        gameState.put(GameStateKeys.IsGameLost, false);

        // Given: making sure
        assertThat(QueryGameState.isGameWon(gameState) == false).isTrue();
        assertThat(QueryGameState.isGameLost(gameState) == false).isTrue();

        // When
        ModifyGameState.declareGameToBeWon(gameState);
        ModifyGameState.declareGameToBeLost(gameState);

        // Then
        assertThat(QueryGameState.isGameWon(gameState) == true).isTrue();
        assertThat(QueryGameState.isGameLost(gameState) == true).isTrue();
    }

    @Test
    void t208_winConditionLossCondition() {
        // Given
        GameState gameState = new CreateGameState().defaultsWithFullDeck();

        String actionsToPerform = "drawSingleCard, drawSingleCard";
        List<IGameAction> actions = new CreateGameActions().havingOrders(actionsToPerform);

        List<IGameCondition> conditions = List.of(
            new DidGuessACard(), new DidTurnsExpire()
        );

        // When
        do {
            for (IGameAction action : actions) {
                action.changeGameState(gameState, null, null);
            }

            for (IGameCondition condition : conditions) {
                condition.checkAndUpdate(gameState);
            }
        } while (QueryGameState.isGameFinished(gameState) == false);

        // Then
        assertThat(QueryGameState.isGameLost(gameState) == true).isTrue();
        assertThat(QueryGameState.isGameWon(gameState) == false).isTrue();
    }

    @Test
    void t213_oneMoreFactory_withNullObject() {
        // Given
        PlayedGameRules referenceRules = new CreatePlayedGameRules().empty();

        // Knowing that
        assertThat(referenceRules.gameActions().size() == 0).isTrue();
        assertThat(referenceRules.victoryConditions().size() == 0).isTrue();
        assertThat(referenceRules.gameStopConditions().size() == 0).isTrue();
        assertThat(referenceRules.cardComparator() instanceof AlwaysFailComparisonStrategy).isTrue();

        // Given the change
        String gameName = "Random game";

        // When
        PlayedGameRules actualRules = new CreatePlayedGameRules().withModifications(gameName, null, null, null, null);

        // Then
        assertThat(actualRules.gameName().equals(gameName)).isTrue();
        assertThat(actualRules.gameActions().size() == referenceRules.gameActions().size()).isTrue();
        assertThat(actualRules.victoryConditions().size() == referenceRules.victoryConditions().size()).isTrue();
        assertThat(actualRules.gameStopConditions().size() == referenceRules.gameStopConditions().size()).isTrue();
        assertThat(actualRules.cardComparator() instanceof AlwaysFailComparisonStrategy).isTrue();

        // Given the changes
        List<IGameAction> actions = List.of(new GuessCardAction());
        List<IGameCondition> victories = List.of(new DidGuessACard());

        // When
        actualRules = new CreatePlayedGameRules().withModifications(null, actions, victories, null, null);

        // Then
        assertThat(actualRules.gameName().equals(referenceRules.gameName())).isTrue();
        assertThat(actualRules.gameActions().get(0) instanceof GuessCardAction).isTrue();
        assertThat(actualRules.victoryConditions().get(0) instanceof DidGuessACard).isTrue();
        assertThat(actualRules.gameStopConditions().size() == referenceRules.gameStopConditions().size()).isTrue();
        assertThat(actualRules.cardComparator() instanceof AlwaysFailComparisonStrategy).isTrue();
    }

    @Test
    void t209_theGameWasAStrategyAllAlong() {
        // Given
        GuessACardGame game = new GuessACardGame();

        // When
        // Then
        assertThat(game.availableActions().size() == 1).isTrue();
        assertThat(game.gameStopConditions().size() == 1).isTrue();
        assertThat(game.victoryConditions().size() == 1).isTrue();

        assertThat(game.availableActions().get(0) instanceof GuessCardAction).isTrue();
        assertThat(game.gameStopConditions().get(0) instanceof DidTurnsExpire).isTrue();
        assertThat(game.victoryConditions().get(0) instanceof DidGuessACard).isTrue();
    }

    @Test
    void t210_builderPatternRevealsItself() {
        // Given
        GameManagerInternalsBuilder builder = new GameManagerInternalsBuilder();

        // When
        new SelectGame().changeGameRuleset(builder, "GuessACard");

        // Then
        PlayedGameRules rules = builder.constructRuleset();

        assertThat(rules.cardComparator() instanceof StrictCardComparisonStrategy).isTrue();

        assertThat(rules.gameActions().get(0) instanceof GuessCardAction).isTrue();
        assertThat(rules.gameStopConditions().get(0) instanceof DidTurnsExpire).isTrue();
        assertThat(rules.victoryConditions().get(0) instanceof DidGuessACard).isTrue();
    }

    @Test
    void t211_gloryOfDeferredConstruction() {
        // Given
        GameManagerInternalsBuilder builder = new GameManagerInternalsBuilder();

        List<ICreateGameRulesCommand> commands = List.of(
            new SelectGame(), new GameVariant()
        );

        List<String> arguments = List.of("GuessACard", "RedBlack");

        // When
        for (int i = 0; i < commands.size(); i++) {
            commands.get(i).changeGameRuleset(builder, arguments.get(i));
        }

        // Then
        PlayedGameRules rules = builder.constructRuleset();

        assertThat(rules.cardComparator() instanceof BlackRedColourOnlyComparisonStrategy).isTrue();

        assertThat(rules.gameActions().get(0) instanceof GuessCardAction).isTrue();
        assertThat(rules.gameStopConditions().get(0) instanceof DidTurnsExpire).isTrue();
        assertThat(rules.victoryConditions().get(0) instanceof DidGuessACard).isTrue();
    }

    @Test
    void t212_implementGuessACardCommand() {
        // Given
        GameManagerInternalsBuilder builder = new GameManagerInternalsBuilder();

        List<ICreateGameRulesCommand> commands = List.of(
            new SelectGame(), new GameVariant(), new SetDeck()
        );

        List<String> arguments = List.of("GuessACard", "RedBlack", "2H,2D,3H,3D");

        for (int i = 0; i < commands.size(); i++) {
            commands.get(i).changeGameRuleset(builder, arguments.get(i));
        }

        PlayedGameRules rules = builder.constructRuleset();
        GameState gameState = builder.constructGameState();

        assertThat(QueryGameState.amountOfCardsLeft(gameState) == 4).isTrue();

        IGameAction action = new GuessCardAction();

        // When
        // First guess is 2S (black), should come a red card, so should be a miss
        action.changeGameState(gameState, rules, "2S");

        // Then
        assertThat((Boolean) gameState.get("Guess") == false).isTrue();

        // When
        // Second guess is 10H (red), should come a red card, so should be a hit
        action.changeGameState(gameState, rules, "10H");

        // Then
        assertThat((Boolean) gameState.get("Guess") == true).isTrue();
    }
}
