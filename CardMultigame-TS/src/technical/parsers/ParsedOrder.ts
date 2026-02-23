export interface ParsedOrder {
  readonly command: string;
  readonly params: string;
}

export function parsedOrder(command: string, params: string): ParsedOrder {
  return { command, params };
}
