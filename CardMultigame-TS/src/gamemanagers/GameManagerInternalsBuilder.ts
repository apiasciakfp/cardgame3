import { CardDeck } from "../entities/decks/CardDeck.js";
import { CreateGameState } from "../entities/gamestates/CreateGameState.js";
import { GameState } from "../entities/gamestates/GameState.js";
import { GameStateKeys } from "../entities/gamestates/GameStateKeys.js";
import { CreatePlayedGameRules } from "./selectedrules/CreatePlayedGameRules.js";
import { PlayedGameRules } from "./selectedrules/PlayedGameRules.js";
import { ICardComparisonStrategy } from "../usecases/cardcomparison/ICardComparisonStrategy.js";
import { IGameAction } from "../usecases/gameactions/IGameAction.js";
import { IGameCondition } from "../usecases/gameconditions/IGameCondition.js";

export class GameManagerInternalsBuilder {
  private _gameName: string | null = null;
  private _deck: CardDeck | null = null;
  private _actions: IGameAction[] | null = null;
  private _victories: IGameCondition[] | null = null;
  private _gameStops: IGameCondition[] | null = null;
  private _initialGameState: GameState | null = null;
  private _compareCards: ICardComparisonStrategy | null = null;

  constructRuleset(): PlayedGameRules {
    return new CreatePlayedGameRules().withModifications(
      this._gameName,
      this._actions,
      this._victories,
      this._gameStops,
      this._compareCards
    );
  }

  constructGameState(): GameState {
    return new CreateGameState().withModifications(
      this._initialGameState,
      this._deck
    );
  }

  setName(name: string): void {
    this._gameName = name;
  }

  setAvailableActions(actions: IGameAction[]): void {
    this._actions = actions;
  }

  setVictoryConditions(victories: IGameCondition[]): void {
    this._victories = victories;
  }

  setGameStopConditions(gameStops: IGameCondition[]): void {
    this._gameStops = gameStops;
  }

  setDeck(cardDeck: CardDeck): void {
    this._deck = cardDeck;
  }

  setInitialGameState(gameState: GameState): void {
    this._initialGameState = gameState;
  }

  setMaxTurns(maxTurns: number): void {
    this._initialGameState!.set(GameStateKeys.MaxTurns, maxTurns);
  }

  getCardDeck(): CardDeck | null {
    return this._deck;
  }

  setCardComparisonStrategy(selected: ICardComparisonStrategy): void {
    this._compareCards = selected;
  }
}
