import { CardDeck } from "../decks/CardDeck.js";
import { CreateCardDeck } from "../decks/CreateCardDeck.js";
import { GameState } from "../gamestates/GameState.js";
import { GameStateKeys } from "../gamestates/GameStateKeys.js";
import { ICardComparisonStrategy } from "../../usecases/cardcomparison/ICardComparisonStrategy.js";
import { StrictCardComparisonStrategy } from "../../usecases/cardcomparison/StrictCardComparisonStrategy.js";
import { GuessCardAction } from "../../usecases/gameactions/GuessCardAction.js";
import { IGameAction } from "../../usecases/gameactions/IGameAction.js";
import { DidGuessACard } from "../../usecases/gameconditions/DidGuessACard.js";
import { DidTurnsExpire } from "../../usecases/gameconditions/DidTurnsExpire.js";
import { IGameCondition } from "../../usecases/gameconditions/IGameCondition.js";
import { IGameImplementation } from "./IGameImplementation.js";

export class GuessACardGame implements IGameImplementation {
  cardDeck(): CardDeck {
    return new CreateCardDeck().simple9ToAWith4Colours();
  }

  availableActions(): IGameAction[] {
    return [new GuessCardAction()];
  }

  gameStopConditions(): IGameCondition[] {
    return [new DidTurnsExpire()];
  }

  victoryConditions(): IGameCondition[] {
    return [new DidGuessACard()];
  }

  initialGameState(): GameState {
    const state = new GameState();
    state.set(GameStateKeys.MaxTurns, 5);
    return state;
  }

  title(): string {
    return "Guess a Card!";
  }

  cardComparisonStrategy(): ICardComparisonStrategy {
    return new StrictCardComparisonStrategy();
  }
}
