import { CardDeck } from "../decks/CardDeck.js";
import { GameState } from "../gamestates/GameState.js";
import { ICardComparisonStrategy } from "../../usecases/cardcomparison/ICardComparisonStrategy.js";
import { IGameAction } from "../../usecases/gameactions/IGameAction.js";
import { IGameCondition } from "../../usecases/gameconditions/IGameCondition.js";

export interface IGameImplementation {
  title(): string;
  cardDeck(): CardDeck;
  availableActions(): IGameAction[];
  victoryConditions(): IGameCondition[];
  gameStopConditions(): IGameCondition[];
  initialGameState(): GameState;
  cardComparisonStrategy(): ICardComparisonStrategy;
}
