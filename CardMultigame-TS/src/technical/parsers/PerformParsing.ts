import { IParseStrategy } from "./parsestrategies/IParseStrategy.js";
import { ParsedOrder, parsedOrder } from "./ParsedOrder.js";

export class PerformParsing {
  private readonly parseStrategy: IParseStrategy;

  constructor(parseStrategy: IParseStrategy) {
    this.parseStrategy = parseStrategy;
  }

  executeOn(orderString: string): ParsedOrder[] {
    const records = this.parseStrategy.splitIntoRecords(orderString);

    const singleFirstWord = /(\b\w+\b){1}/;

    const actionsWithParams: ParsedOrder[] = [];
    for (const record of records) {
      const match = record.match(singleFirstWord);

      let actionSigil = "";
      if (match) {
        actionSigil = match[0];
      }

      const paramsSigil = record.replace(actionSigil, "");

      actionsWithParams.push(
        parsedOrder(actionSigil.trim(), paramsSigil.trim())
      );
    }

    return actionsWithParams;
  }
}
