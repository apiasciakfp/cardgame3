package com.cardmultigame.entities.gamestates;

import java.util.HashMap;

/**
 * This is for readability ONLY. An example implementation of
 * EncapsulatedContext pattern is a HashMap of this type
 * passed where needed.
 *
 * Do not do this in the real world systems unless you REALLY know
 * what you are doing.
 */
public class GameState extends HashMap<String, Object> {
    // Java HashMap.get() already returns null for missing keys,
    // matching the C# override behavior (C# Dictionary throws KeyNotFoundException).
}
