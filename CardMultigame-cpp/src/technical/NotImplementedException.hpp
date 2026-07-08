#pragma once

// Non-mirror helper: C++ has no NotImplementedException. Maps C# NotImplementedException, thrown by
// the dormant special-rule actions' ShouldReactTo (WART-14). (Exception mapping — DA #8b.)

#include <stdexcept>

namespace cardmultigame::technical
{
    class NotImplementedException : public std::logic_error
    {
    public:
        NotImplementedException() : std::logic_error("The method or operation is not implemented.") {}
    };
}
