import { CreateGameState } from "../entities/gamestates/CreateGameState.js";
import { GameState } from "../entities/gamestates/GameState.js";
import { CreatePlayedGameRules } from "./selectedrules/CreatePlayedGameRules.js";
import { PlayedGameRules } from "./selectedrules/PlayedGameRules.js";
import { CreateGameStructure } from "./selectedrules/CreateGameStructure.js";
import { SelectedParser } from "../technical/parsers/SelectedParser.js";
import { GameManager } from "./GameManager.js";

export class CreateGameManager {
  defaultsWithOrders(orderString: string): GameManager {
    const orders = new SelectedParser().properlyParse(orderString);

    const builder = new CreateGameStructure().buildRulesAndInitialState(orders);

    const rules = builder.constructRuleset();
    const initialState = builder.constructGameState();

    return new GameManager(initialState, rules);
  }

  empty(): GameManager {
    const initialState = new CreateGameState().defaultState();
    const rules = new CreatePlayedGameRules().empty();

    return new GameManager(initialState, rules);
  }
}
