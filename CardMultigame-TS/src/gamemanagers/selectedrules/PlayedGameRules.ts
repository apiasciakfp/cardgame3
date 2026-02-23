import { GameState } from "../../entities/gamestates/GameState.js";
import { ICardComparisonStrategy } from "../../usecases/cardcomparison/ICardComparisonStrategy.js";
import { IGameAction } from "../../usecases/gameactions/IGameAction.js";
import { IGameCondition } from "../../usecases/gameconditions/IGameCondition.js";

export class PlayedGameRules {
  private readonly _gameName: string;
  private readonly _actions: IGameAction[];
  private readonly _victoryConditions: IGameCondition[];
  private readonly _gameStopConditions: IGameCondition[];
  private readonly _cardComparator: ICardComparisonStrategy;

  constructor(
    gameName: string,
    actions: IGameAction[],
    victories: IGameCondition[],
    gameStops: IGameCondition[],
    compareCards: ICardComparisonStrategy
  ) {
    this._gameName = gameName;
    this._actions = actions;
    this._victoryConditions = victories;
    this._gameStopConditions = gameStops;
    this._cardComparator = compareCards;
  }

  cardComparator(): ICardComparisonStrategy {
    return this._cardComparator;
  }

  gameActions(): IGameAction[] {
    return this._actions;
  }

  victoryConditions(): IGameCondition[] {
    return this._victoryConditions;
  }

  gameStopConditions(): IGameCondition[] {
    return this._gameStopConditions;
  }

  gameName(): string {
    return this._gameName;
  }

  checkVictoryConditions(currentGameState: GameState): void {
    for (const victory of this._victoryConditions) {
      victory.checkAndUpdate(currentGameState);
    }
  }

  checkGameStopConditions(currentGameState: GameState): void {
    for (const stop of this._gameStopConditions) {
      stop.checkAndUpdate(currentGameState);
    }
  }
}
