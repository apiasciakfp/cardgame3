#pragma once

#include <random>

namespace cardmultigame::technical::rangens
{
    // Non-mirror helper: reproduces .NET System.Random.Next(minValue, maxValue) semantics —
    // maxValue is EXCLUSIVE. This is what makes RandomCardSelector's `Next(0, count-1)` never
    // draw the last card for count>=2 (WART-13). Do NOT replace with a naive
    // uniform_int_distribution(0, count-1). Seeded (weakly) from a millisecond component, mirroring
    // `new Random(DateTime.Now.Millisecond)`.
    class DotnetRandom
    {
        std::mt19937 _engine;

    public:
        DotnetRandom();
        explicit DotnetRandom(unsigned int seed);

        // .NET Next(min, max): min==max -> min; max<min -> throw; else uniform in [min, max-1].
        int Next(int minValue, int maxValue);
    };
}
