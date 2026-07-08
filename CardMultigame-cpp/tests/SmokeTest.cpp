// SmokeTest — re-targeted from Java's SmokeTest (which asserts the runtime version).
// Slice 0: proves the toolchain compiles+links+runs doctest under C++20.
// The library-link assertion grows once real symbols exist (Slice 1+).
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("toolchain provides C++20")
{
    CHECK(__cplusplus >= 202002L);
}
