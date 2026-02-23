import { GuessACardGame } from "../../../entities/games/GuessACardGame.js";
import { IGameImplementation } from "../../../entities/games/IGameImplementation.js";
import { GameManagerInternalsBuilder } from "../../GameManagerInternalsBuilder.js";
import { ICreateGameRulesCommand } from "./ICreateGameRulesCommand.js";

export class SelectGame implements ICreateGameRulesCommand {
  private identifier = "Play";

  changeGameRuleset(
    builder: GameManagerInternalsBuilder,
    parameters: string
  ): void {
    const gameImpl = SelectGame.selectGameImplementation(parameters);

    builder.setName(gameImpl.title());
    builder.setDeck(gameImpl.cardDeck());
    builder.setAvailableActions(gameImpl.availableActions());
    builder.setVictoryConditions(gameImpl.victoryConditions());
    builder.setGameStopConditions(gameImpl.gameStopConditions());
    builder.setInitialGameState(gameImpl.initialGameState());
    builder.setCardComparisonStrategy(gameImpl.cardComparisonStrategy());
  }

  shouldReactTo(outerCommandName: string): boolean {
    return this.identifier.toLowerCase() === outerCommandName.toLowerCase();
  }

  private static selectGameImplementation(
    parameters: string
  ): IGameImplementation {
    let gameImpl: IGameImplementation | null = null;
    if (parameters.toLowerCase() === "guessacard") {
      gameImpl = new GuessACardGame();
    }

    if (gameImpl === null)
      throw new Error(
        "Either the game is not registered in factory or game identifier has a typo. Got: " +
          parameters
      );

    return gameImpl;
  }
}
