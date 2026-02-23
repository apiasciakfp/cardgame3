/**
 * This is for readability ONLY. An example implementation of
 * EncapsulatedContext pattern is a Map of this type
 * passed where needed.
 *
 * Do not do this in the real world systems unless you REALLY know
 * what you are doing.
 */
export class GameState extends Map<string, unknown> {
  // JS Map.get() already returns undefined for missing keys,
  // matching the C# override behavior (C# Dictionary throws KeyNotFoundException).
}
