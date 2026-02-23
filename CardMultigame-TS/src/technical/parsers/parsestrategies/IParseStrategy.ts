export interface IParseStrategy {
  separator(): string;
  splitIntoRecords(orderString: string): string[];
}
