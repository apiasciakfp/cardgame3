#include "technical/rangens/DotnetRandom.hpp"

#include <chrono>
#include <stdexcept>

namespace cardmultigame::technical::rangens
{
    namespace
    {
        unsigned int MillisecondSeed()
        {
            const auto now = std::chrono::system_clock::now().time_since_epoch();
            const auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
            return static_cast<unsigned int>(millis % 1000); // the 0..999 ms component, like DateTime.Now.Millisecond
        }
    }

    DotnetRandom::DotnetRandom()
        : _engine(MillisecondSeed())
    {
    }

    DotnetRandom::DotnetRandom(unsigned int seed)
        : _engine(seed)
    {
    }

    int DotnetRandom::Next(int minValue, int maxValue)
    {
        if (maxValue < minValue)
        {
            throw std::invalid_argument("minValue must be less than or equal to maxValue");
        }
        if (minValue == maxValue)
        {
            return minValue;
        }
        std::uniform_int_distribution<int> distribution(minValue, maxValue - 1);
        return distribution(_engine);
    }
}
