import { ICardComparisonStrategy } from "../../usecases/cardcomparison/ICardComparisonStrategy.js";
import { CreateCardComparisonStrategy } from "../../usecases/cardcomparison/CreateCardComparisonStrategy.js";
import { IGameAction } from "../../usecases/gameactions/IGameAction.js";
import { IGameCondition } from "../../usecases/gameconditions/IGameCondition.js";
import { PlayedGameRules } from "./PlayedGameRules.js";

export class CreatePlayedGameRules {
  private defaultGameName = "No game selected";
  private defaultActions: IGameAction[] = [];
  private defaultVictories: IGameCondition[] = [];
  private defaultGameStops: IGameCondition[] = [];
  private defaultCardComparators: ICardComparisonStrategy =
    new CreateCardComparisonStrategy().none();

  empty(): PlayedGameRules {
    return new PlayedGameRules(
      this.defaultGameName,
      this.defaultActions,
      this.defaultVictories,
      this.defaultGameStops,
      this.defaultCardComparators
    );
  }

  withModifications(
    gameName: string | null,
    actions: IGameAction[] | null,
    victories: IGameCondition[] | null,
    gameStops: IGameCondition[] | null,
    compareCards: ICardComparisonStrategy | null
  ): PlayedGameRules {
    let selectedName = this.defaultGameName;
    let selectedActions = this.defaultActions;
    let selectedVictories = this.defaultVictories;
    let selectedGameStops = this.defaultGameStops;
    let selectedCardComparators = this.defaultCardComparators;

    if (gameName !== null) selectedName = gameName;
    if (actions !== null) selectedActions = actions;
    if (victories !== null) selectedVictories = victories;
    if (gameStops !== null) selectedGameStops = gameStops;
    if (compareCards !== null) selectedCardComparators = compareCards;

    return new PlayedGameRules(
      selectedName,
      selectedActions,
      selectedVictories,
      selectedGameStops,
      selectedCardComparators
    );
  }
}
