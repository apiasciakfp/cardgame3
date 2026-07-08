# CardMultigame — C++ port

A **faithful, surface-idiomatic C++20 port** of CardMultigame, the deliberately over-engineered
GoF-design-patterns training app. Ported class-by-class from the C# original (canonical), with the
Java port as the primary template. **Every deliberate wart and every design pattern is preserved** —
this is a transliteration (natural C++ syntax, zero semantic drift), not a clean rewrite.

Sibling of `CardMultigame-Java`, `CardMultigame-TS`, `CardMultigame-Python`.

## Requirements

- **GCC 11.4+** (or any C++20 compiler; no `<format>`/C++23 features used)
- **CMake 3.22+** and **Make**
- No package manager needed — the test framework (doctest) is vendored in `tests/doctest.h`.

## Build, test, run

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build            # 37 cases / 211 assertions — the 7 Java test files
./build/cardmultigame             # the REPL
```

### Playing the REPL

Type a setup string ending in `SETUP`, then `Guess <card>` commands; `EXIT` to quit:

```
Play GuessACard; SetDeck JH,QH,KH; SetMaxTurns 3; SETUP
Guess QH;
EXIT
```

## Layout

Mirrors the C# `Core/` tree one-class-per-file (`.hpp`/`.cpp` pairs; interfaces are header-only
abstract classes):

```
src/
  main.cpp                        REPL entry (mirrors Program.cs)
  interface/UiLogicDispatcher     display + setup/dispatch
  entities/{cards,decks,games,gamestates}
  gamemanagers/{,selectedrules/{,creationcommands}}
  technical/{parsers/{,parsestrategies},rangens}
  usecases/{cardcomparison,gameactions,gameconditions,influencestate}
  technical/StringUtils.hpp        non-mirror helper (trim/split/replace-all — C++ stdlib gaps)
  technical/NotImplementedException.hpp   non-mirror helper (dormant-action throw)
  technical/rangens/DotnetRandom   non-mirror helper (.NET Random.Next semantics — WART-13)
tests/                            the 7 Java test files as doctest + vendored doctest.h
scripts/differential_oracle.sh    REPL byte-diff vs the Python port (== C#), deck line masked
```

## Notable faithful choices (do not "fix" these)

- `Card` is a plain class with **no `operator==`** — reference (identity) equality, as C#. The deck
  erases the drawn card by pointer identity.
- `GameState` is a `string -> std::any` insertion-ordered bag (not a typed struct): missing key
  returns an empty `std::any`, and the REPL prints every value via an exhaustive `any_cast` dispatch.
- `RandomCardSelector` uses a `.NET Random.Next(0, count-1)` helper (max-exclusive) → it never draws
  the last card for decks of ≥2 (a hidden wart; intentionally not covered by any test).
- The parser keeps the dead-code trim, the `pos > 0` separator guard, and replace-all param extraction.
- 25 deliberate warts total — see the analysis in the sibling task folder.

**Not committed** by design — review and commit at your discretion.
