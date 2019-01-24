using Core.Containers.GameManagers.Rules.CreationCommands;
using Core.Containers.GameRules;
using Core.Containers.GameRules.CreationCommands;
using Core.Entities.Cards;
using Core.Entities.Decks;
using Core.Entities.Games;
using Core.Entities.GameStates;
using Core.GameManagers.SelectedRules;
using Core.Usecases.CardComparison;
using Core.Usecases.GameActions;
using Core.Usecases.GameConditions;
using Core.Usecases.InfluenceState;
using NUnit.Framework;
using System.Collections.Generic;
using System.Linq;

namespace TrainingTests
{

    public class Batch_200
    {

        [Test]
        public void T_201_GentleIntroductionToCommand()
        {
            // Commentary
            // ---
            // Joking. There is no 'gentle' in 'Command'.
            //
            // Now, our Commands use shared mutable state called 'GameState', which makes it a bit harder
            // to understand and make sensible tests. Do not worry, ignore it for now - will come with time.
            //
            // Also do not be scared of 'null' in those tests. We are doing baby steps, introducing gradually more
            // stuff one by one.
            //
            // Your first task is to make a Command which draws a single random card. And does nothing more.
            // Read the tutorial to understand how. You may even Ctrl+C -> Ctrl+V some tutorial code for now.
            // ---

            // Tutorial: how to extract the CardDeck from the GameState
                // Having the GameState:
            GameState tutorialState = new GameStateFactory().DefaultsWithFullDeck();
                // We can extract CardDeck and draw a random card:
            CardDeck tutorialDeck = QueryGameState.ExtractCardDeck(tutorialState);
            tutorialDeck.DrawRandomCard();
            // End of tutorial.

            // Given
            CardDeck deck = new CardDeckFactory().FromGivenCards("2H, 3H, 4H");
            GameState gameState = new GameStateFactory().DefaultsPlusDeck(deck);

            // Expected:
            Assert.IsTrue(QueryGameState.AmountOfCardsLeft(gameState) == 3);
            int amountOfCardsAfterDrawingOne = QueryGameState.AmountOfCardsLeft(gameState) - 1;

            // When
            new DrawSingleCardAction().ChangeGameState(gameState, null, null);

            // Then
            Assert.IsTrue(QueryGameState.AmountOfCardsLeft(gameState) == amountOfCardsAfterDrawingOne);

        }

        [Test]
        public void T_202_AddSome_QH_IntoTheCardDeck()
        {
            // Commentary
            // ---
            // Let's first focus on the differences between the command and the strategy.
            // So let us make a new command - one which will insert a new card into the deck.
            // For simplification, let it be QH (Queen of Hearts).
            //
            // And let's make a list of it and run it 5 times.
            // ---

            // Given
            CardDeck deck = new CardDeckFactory().FromGivenCards("2H, 3H, 4H");
            GameState gameState = new GameStateFactory().DefaultsPlusDeck(deck);

            List<IGameAction> actions = new List<IGameAction>()
            {
                new AddQueenOfHeartsToDeck(),
                new AddQueenOfHeartsToDeck(),
                new AddQueenOfHeartsToDeck(),
                new AddQueenOfHeartsToDeck(),
                new AddQueenOfHeartsToDeck()
            };

            // Expected:
            Assert.IsTrue(QueryGameState.AmountOfCardsLeft(gameState) == 3);
            int amountOfCardsAfterDrawingOne = QueryGameState.AmountOfCardsLeft(gameState) + actions.Count();

            // When
            foreach (var action in actions)
            {
                action.ChangeGameState(gameState, null, null);
            }

            // Then
            Assert.IsTrue(QueryGameState.AmountOfCardsLeft(gameState) == amountOfCardsAfterDrawingOne);

            CardDeck retrievedDeck = QueryGameState.ExtractCardDeck(gameState);

            for (int i=0; i<5; i++)
            {
                Card card = retrievedDeck.DrawLastAddedCard();

                Assert.IsTrue(card.Rank() == "Q");
                Assert.IsTrue(card.Colour() == "H");
            }
        }

        [Test]
        public void T_203_ChainSomeCommands()
        {
            // Commentary
            // ---
            // So far, so good. Now, this is going to be fun. 
            // We will make a new command called Add10COrDrawACard which will
            //
            // * add a 10C if there is an even amount of cards (2-4-6)
            // or 
            // * draw a card if there is an odd amount of cards (1-3-5)
            //
            // And we are going to make a chain of DIFFERENT commands.
            //
            // Note: depending on the ORDER of chaining, the result will be different.
            // ---

            // Given
            CardDeck deck = new CardDeckFactory().FromGivenCards("2H, 3H, 4H");
            GameState gameState = new GameStateFactory().DefaultsPlusDeck(deck);

            List<IGameAction> actions = new List<IGameAction>()
            {
                new DrawSingleCardAction(),
                new DrawSingleCardAction(),
                new DrawSingleCardAction(),     // now it should be empty
                new AddQueenOfHeartsToDeck(),
                new AddQueenOfHeartsToDeck(),
                new Add10COrDrawACard(),        // should add +1 card, because even
                new Add10COrDrawACard()         // should draw a card, because odd
            };

            // Expected:
            Assert.IsTrue(QueryGameState.AmountOfCardsLeft(gameState) == 3);
            int amountOfCardsAfterDrawingOne = 2;

            // When
            foreach (var action in actions)
            {
                action.ChangeGameState(gameState, null, null);
            }

            // Then
            Assert.IsTrue(QueryGameState.AmountOfCardsLeft(gameState) == amountOfCardsAfterDrawingOne);

        }

        [Test]
        public void T_204_FactorizeMe()
        {
            // Commentary
            // ---
            // But THIS means it is possible to do it using a factory. So, same test, but with a factory now.
            // Hint: string.Split(','); string.Trim(); List.Add; foreach; are your best friends in this task.
            // ---

            // Given
            CardDeck deck = new CardDeckFactory().FromGivenCards("2H, 3H, 4H");
            GameState gameState = new GameStateFactory().DefaultsPlusDeck(deck);

            string actionsToPerform = "drawSingleCard, drawSingleCard, drawSingleCard, addQH, addQH, " +
                "add10cOrDraw, add10cOrDraw";
            List<IGameAction> actions = new GameActionsFactory().HavingOrders(actionsToPerform);

            // Expected:
            Assert.IsTrue(QueryGameState.AmountOfCardsLeft(gameState) == 3);
            int amountOfCardsAfterDrawingOne = 2;

            // When
            foreach (var action in actions)
            {
                action.ChangeGameState(gameState, null, null);
            }

            // Then
            Assert.IsTrue(QueryGameState.AmountOfCardsLeft(gameState) == amountOfCardsAfterDrawingOne);
        }

        [Test]
        public void T_205_CommandsCanCommunicateViaContext()
        {
            // Commentary
            // ---
            // As commands share a common state - the GameState - they are like sequential machines operating
            // on the same conveyor belt. This allows two commands to communicate via Context (GameState).
            //
            // Look at the 'Tutorial' section of this test. It shows how to insert something into 
            // the State object and how to retrieve something from it.
            //
            // Then, if 'DrawSingleCardAction' draws a last card, it should additionally write:
            // {KEY: 'Guess' VALUE: true} into the gameState. 'True' here is a bool, not a string, mind you.
            //
            // We will need it later, for GuessCardAction command.
            // ---

            // Tutorial
            GameState tutorialState = new GameStateFactory().Default();
                // The key 'SpecificKey' does not exist...
            Assert.IsTrue(tutorialState["SpecificKey"] == null);
                // ...thus we insert it in...
            tutorialState["SpecificKey"] = "Capybara";
                // ...and now it exists.
            Assert.IsTrue(tutorialState["SpecificKey"] as string == "Capybara");

            // Given
            CardDeck deck = new CardDeckFactory().FromGivenCards("2H, 3H, 4H");
            GameState gameState = new GameStateFactory().DefaultsPlusDeck(deck);

            string actionsToPerform = "drawSingleCard, drawSingleCard, drawSingleCard";
            List<IGameAction> actions = new GameActionsFactory().HavingOrders(actionsToPerform);

            // Expected:
            Assert.IsTrue(QueryGameState.AmountOfCardsLeft(gameState) == 3);

            // When
            foreach (var action in actions)
            {
                action.ChangeGameState(gameState, null, null);
            }

            // Then
            Assert.IsTrue(gameState["Guess"] as bool? == true);
        }

        [Test]
        public void T_206_QueryGameState_CannotChangeAThing()
        {
            // Commentary
            // ---
            // GameState is a very simple bag you can put everything into and try to extract it from.
            // To avoid making 9999 specialized methods, a Facade functions have been introduced - Queries and Changes.
            // 
            // Queries are Facade functions which make it simpler to work with GameState. Instead of remembering
            // how to address particular keys, Queries simply implement the common 'questions' to the GameState.
            //
            // In a way, they are the API to the incomprehensible GameState.
            //
            // You will have to implement two Queries: IsGameLost() and IsGameWon(). Look at Given to see
            // which keys you will work with. Remember you may have to cast to bool:
            //
            // bool xxx = (bool)objectWhichMayBeABool;
            // ---

            // Given
            GameState gameState = new GameStateFactory().Default();
            gameState[GameStateKeys.IsGameWon] = false;
            gameState[GameStateKeys.IsGameLost] = false;

            // When
            // Then
            Assert.IsTrue(QueryGameState.IsGameWon(gameState) == false);
            Assert.IsTrue(QueryGameState.IsGameLost(gameState) == false);
        }

        [Test]
        public void T_207_ModifyGameState_CanChangeQuiteALot()
        {
            // Commentary
            // ---
            // 
            // As much as Queries are Facade functions, so are the ModifyGameState functions - also Facade functions.
            //
            // Queries could only ask GameState 'what is X'. Modifications can change the state of
            // GameState. Therefore they are much more dangerous.
            //
            // After completing this test you should know how to work with EncapsulatedContext (GameState) 
            // and how to extract stuff from it using Queries and change it using Modifications.
            // ---

            // Given
            GameState gameState = new GameStateFactory().Default();
            gameState[GameStateKeys.IsGameWon] = false;
            gameState[GameStateKeys.IsGameLost] = false;

            // Given: making sure
            Assert.IsTrue(QueryGameState.IsGameWon(gameState) == false);
            Assert.IsTrue(QueryGameState.IsGameLost(gameState) == false);

            // When
            ModifyGameState.DeclareGameToBeWon(gameState);
            ModifyGameState.DeclareGameToBeLost(gameState);

            // Then
            Assert.IsTrue(QueryGameState.IsGameWon(gameState) == true);
            Assert.IsTrue(QueryGameState.IsGameLost(gameState) == true);

        }

        [Test]
        public void T_208_WinConditionLossCondition()
        {
            // Commentary
            // ---
            // To be able to understand the core loop of this program we need to build a different
            // type of command - the Conditions type of command.
            // 
            // We are going to implement two Conditions: DidGuessACard and DidTurnsExpire.
            //
            // We will: 
            // * chain two DrawSingleActionCards together
            // * chain DidGuessACard and DidTurnsExpire
            //
            // And they should:
            // * DidGuessACard is supposed to set victory (ModifyGameState.DeclareGameToBeWon) IF 'Guess' is true.
            // * DidTurnsExpire is supposed to set a loss (ModifyGameState.DeclareGameToBeLost) IF currentTurn >= maxTurns.
            //
            // 'Guess' will be true when we draw a last card via DrawSingleCardAction. Remember? You implemented it before.
            //
            // Also, look at the structure of 'When' in this test.
            // THIS is the core game loop.  If you look at GameManager, you will see the same concept, 
            // but with slightly different implementation.
            //
            // Two Chains of Responsibility.
            // ---

            // Given
            GameState gameState = new GameStateFactory().DefaultsWithFullDeck();

            string actionsToPerform = "drawSingleCard, drawSingleCard";
            List<IGameAction> actions = new GameActionsFactory().HavingOrders(actionsToPerform);

            List<IGameCondition> conditions = new List<IGameCondition>()
            {
                new DidGuessACard(), new DidTurnsExpire()
            };

            // When

            do
            {
                foreach (var action in actions)
                {
                    action.ChangeGameState(gameState, null, null);
                }

                foreach (var condition in conditions)
                {
                    condition.CheckAndUpdate(gameState);
                }

            } while (QueryGameState.IsGameFinished(gameState) == false);

            // Then
            Assert.IsTrue(QueryGameState.IsGameLost(gameState) == true);
            Assert.IsTrue(QueryGameState.IsGameWon(gameState) == false);
        }

        [Test]
        public void T_209_TheGameWasAStrategyAllAlong()
        {
            // Commentary
            // ---
            // Knowing what we do at this point we can revisit the GuessACardGame.
            // This one is a Strategy. One wide Strategy, to add - with many methods.
            // That particular game uses the configuration as presented in asserts
            // ---

            // Given
            GuessACardGame game = new GuessACardGame();

            // When
            // Then

                // All the actions are only of length 1
            Assert.IsTrue(game.AvailableActions().Count == 1);
            Assert.IsTrue(game.GameStopConditions().Count == 1);
            Assert.IsTrue(game.VictoryConditions().Count == 1);
            
                // And the correct actions are set in appropriate places
            Assert.IsTrue(game.AvailableActions()[0] is GuessCardAction);
            Assert.IsTrue(game.GameStopConditions()[0] is DidTurnsExpire);
            Assert.IsTrue(game.VictoryConditions()[0] is DidGuessACard);
        }

        [Test]
        public void T_210_BuilderPatternRevealsItself()
        {
            // Commentary
            // ---
            // So GuessACardGame is a Strategy. But Strategy always configures something.
            // In this particular application we have to deal with the chains of commands 
            // and with the fact we can change the variants of the game.
            // Like a RedAndBlack variant.
            // 
            // Builder pattern is a tool allowing us to defer the construction of an object to the point it
            // is actually needed.
            //
            // The mechanism which takes place here is present in CreateGameStructure class.
            // So, in this test, create a command SelectGame by setting appropriate builder methods.
            // Builder pattern is implemented for you.
            //
            // Spoiler: you might have noticed that SelectGame() also has the function of a factory.
            // If you look at test 110 (parsers) you will see THIS is where the parameter arrives.
            // ---

            // Given
            GameManagerInternalsBuilder builder = new GameManagerInternalsBuilder();

            // When
            new SelectGame().ChangeGameRuleset(builder, "GuessACard");

            // Then
            PlayedGameRules rules = builder.ConstructRuleset();

            Assert.IsTrue(rules.CardComparator() is StrictCardComparisonStrategy);

            // And those below come from our GuessACardGame
            Assert.IsTrue(rules.GameActions()[0] is GuessCardAction);
            Assert.IsTrue(rules.GameStopConditions()[0] is DidTurnsExpire);
            Assert.IsTrue(rules.VictoryConditions()[0] is DidGuessACard);
        }

        [Test]
        public void T_211_GloryOfDeferredConstruction()
        {
            // Commentary
            // ---
            // Why would we use a builder, then?
            // Because we want to implement a BlackRed variant.
            //
            // Remember the BlackRedColourOnlyComparisonStrategy you implemented earlier?
            // Now it is time to create a GameVariant command which will set the comparator
            // to the BlackRed one.
            //
            // Normally, this takes place in CreateGameStructure.BuildRulesAndInitialState
            // ---

            // Given
            GameManagerInternalsBuilder builder = new GameManagerInternalsBuilder();

            List<ICreateGameRulesCommand> commands = new List<ICreateGameRulesCommand>()
            {
                new SelectGame(), new GameVariant()
            };

            List<string> arguments = new List<string>() { "GuessACard", "RedBlack" };

            // When
            for (int i=0; i < commands.Count; i++)
            {
                commands[i].ChangeGameRuleset(builder, arguments[i]);
            }

            // Then
            PlayedGameRules rules = builder.ConstructRuleset();

            // This comes from the new command.
            Assert.IsTrue(rules.CardComparator() is BlackRedColourOnlyComparisonStrategy);

            // And those below come from our GuessACardGame
            Assert.IsTrue(rules.GameActions()[0] is GuessCardAction);
            Assert.IsTrue(rules.GameStopConditions()[0] is DidTurnsExpire);
            Assert.IsTrue(rules.VictoryConditions()[0] is DidGuessACard);
        }

        [Test]
        public void T_212_ImplementGuessACardCommand()
        {
            // Commentary
            // ---
            // Now, time for a fun task. You know everything needed to implement GuessACard command:
            // * You know how PlayedRules and GameState are made (via builder)
            // * You know what the GuessACard command is:
            //   * It draws a card like the 'DrawSingleCard' command
            //   * It uses a CardComparator taken from Rules to match the card with the one from the parameter
            //     * If it matches it, it puts 'Guess' with 'true'.
            //     * If it doesn't match it, it puts 'Guess' with 'false'.
            //   * It adds +1 turn (method of GameState).
            // Good luck ;-)
            // ---

            // Given
            GameManagerInternalsBuilder builder = new GameManagerInternalsBuilder();

            List<ICreateGameRulesCommand> commands = new List<ICreateGameRulesCommand>()
            {
                new SelectGame(), new GameVariant(), new SetDeck()
            };

            List<string> arguments = new List<string>() { "GuessACard", "RedBlack", "2H,2D,3H,3D" };

            for (int i = 0; i < commands.Count; i++)
            {
                commands[i].ChangeGameRuleset(builder, arguments[i]);
            }

            PlayedGameRules rules = builder.ConstructRuleset();
            GameState gameState = builder.ConstructGameState();

            Assert.IsTrue(QueryGameState.AmountOfCardsLeft(gameState) == 4);

            IGameAction action = new GuessCardAction();

            // When
            // First guess is 2S (black), should come a red card, so should be a miss
            action.ChangeGameState(gameState, rules, "2S");

            // Then
            Assert.IsTrue(gameState["Guess"] as bool? == false);

            // When
            // Second guess is 10H (red), should come a red card, so should be a hit
            action.ChangeGameState(gameState, rules, "10H");

            // Then
            Assert.IsTrue(gameState["Guess"] as bool? == true);

        }

        [Test]
        public void T_213_OneMoreFactory_WithNullObject()
        {
            // Commentary
            // ---
            // Factories can also hold defaults. They either read those from the database / config or hold it in its defaults.
            // This is a fate of CreatePlayedGameRules class - the factory which creates the rules we will actually be playing.
            //
            // Your goal is to make sure it is possible to properly build those rules in such a way that there never exists 
            // a state of the application where there is an exception without us having a very good reason ;-). 
            // In short: a sensible NullObject / Factory interaction.
            // ---

            // Given 
            PlayedGameRules referenceRules = new PlayedGameRulesFactory().Empty();

            // Knowing that
            Assert.IsTrue(referenceRules.GameActions().Count() == 0);
            Assert.IsTrue(referenceRules.VictoryConditions().Count() == 0);
            Assert.IsTrue(referenceRules.GameStopConditions().Count() == 0);
            Assert.IsTrue(referenceRules.CardComparator() is AlwaysFailComparisonStrategy);

            // Given the change
            string gameName = "Random game";

            // When
            PlayedGameRules actualRules = new PlayedGameRulesFactory().WithModifications(gameName, null, null, null, null);

            // Then
            Assert.IsTrue(actualRules.GameName() == gameName);
            Assert.IsTrue(actualRules.GameActions().Count() == referenceRules.GameActions().Count());
            Assert.IsTrue(actualRules.VictoryConditions().Count() == referenceRules.VictoryConditions().Count());
            Assert.IsTrue(actualRules.GameStopConditions().Count() == referenceRules.GameStopConditions().Count());
            Assert.IsTrue(actualRules.CardComparator() is AlwaysFailComparisonStrategy);

            // Given the changes
            var actions = new List<IGameAction>() { new GuessCardAction() };
            var victories = new List<IGameCondition>() { new DidGuessACard() };

            // When
            actualRules = new PlayedGameRulesFactory().WithModifications(null, actions, victories, null, null);

            // Then
            Assert.IsTrue(actualRules.GameName() == referenceRules.GameName());
            Assert.IsTrue(actualRules.GameActions()[0] is GuessCardAction);
            Assert.IsTrue(actualRules.VictoryConditions()[0] is DidGuessACard);
            Assert.IsTrue(actualRules.GameStopConditions().Count() == referenceRules.GameStopConditions().Count());
            Assert.IsTrue(actualRules.CardComparator() is AlwaysFailComparisonStrategy);

        }
    }

}
