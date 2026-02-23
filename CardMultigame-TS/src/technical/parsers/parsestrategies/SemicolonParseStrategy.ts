import { IParseStrategy } from "./IParseStrategy.js";

export class SemicolonParseStrategy implements IParseStrategy {
  private readonly _separator = ";";

  separator(): string {
    return this._separator;
  }

  splitIntoRecords(orderString: string): string[] {
    const records = orderString.split(this._separator);

    const sanitizedRecords: string[] = [];
    for (const record of records) {
      if (record !== null && record.length > 0) {
        // BUG (faithful to C# original): trims into 'sanitized' but checks/adds 'record' (untrimmed).
        const sanitized = record.trim();
        if (record !== null && record.length > 0) {
          sanitizedRecords.push(record);
        }
      }
    }
    return sanitizedRecords;
  }
}
