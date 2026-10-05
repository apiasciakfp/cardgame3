# CardMultigame — PHP port

A **faithful, surface-idiomatic PHP 8.3 port** of CardMultigame, the deliberately over-engineered
GoF-design-patterns training app. Ported class by class from the C# original (canonical), with the Java
port as the template for the tests. **Every deliberate wart and every design pattern is preserved.** This is a
transliteration (natural PHP syntax, zero semantic drift), not a clean rewrite.

Sibling of `CardMultigame-Java`, `CardMultigame-TS`, `CardMultigame-Python`, `CardMultigame-cpp`.

## Requirements

- **PHP 8.3+** CLI with `mbstring` (Ubuntu: `sudo apt install php8.3-cli php8.3-xml php8.3-mbstring composer`)
- **Composer 2**: installs PHPUnit 12 (dev dependency)
- For the differential oracle only: the **.NET SDK** (runs the C# original; see below)

## Install, test, run

```sh
composer install
vendor/bin/phpunit                  # 38 tests: the 7 Java test files
php bin/cardmultigame               # the REPL
scripts/differential_oracle.sh      # REPL vs the real C# binary, 30 transcripts
scripts/structural_gates.sh         # greps for PHP idioms that silently change C# behaviour
```

### Playing the REPL

There is no graphical UI. The C# original's UI is this console loop. Type a setup string ending in `SETUP`,
then `Guess <card>` commands; `EXIT` to quit:

```
Play GuessACard; SetDeck JH,QH,KH; SetMaxTurns 3; SETUP
Guess QH;
EXIT
```

Or pipe a transcript (a "simulated UI"): `printf 'Play GuessACard; SetDeck 2C,3C; SETUP\nGuess 3C;\nEXIT\n' | php bin/cardmultigame`

## Layout

Mirrors the C# `Core/` tree one class per file, PSR-4 namespace `CardMultigame\` = folder path:

```
bin/cardmultigame                 REPL entry (mirrors CardMultigame/Program.cs)
src/
  Interface/UiLogicDispatcher     display + setup/dispatch
  Entities/{Cards,Decks,Games,GameStates}
  GameManagers/{,SelectedRules/{,CreationCommands}}
  Technical/Parsers/{,ParseStrategies}, Technical/RanGens
  Usecases/{CardComparison,GameActions,GameConditions,InfluenceState}
tests/                            the 7 Java test files (Java class and method names kept)
scripts/differential_oracle.sh    REPL byte-diff vs the real C# binary
scripts/structural_gates.sh       porting-rule greps
```

Names follow C# (PascalCase methods become camelCase; `GameStateKeys::CurrentTurn` keeps its C# name).
C#'s namespaces don't always match its folders; PSR-4 requires that they do, so folders win.

## Non-mirror helpers (and why each exists)

PHP lacks some .NET semantics that the C# code relies on silently. Each gap gets one small helper:

| Helper | .NET behaviour it supplies | What plain PHP would do instead |
|---|---|---|
| `Technical/PhpErrorsAsExceptions` | C# **throws** on a missing dictionary key, out-of-range index, null dereference | warn, return `null`, and keep playing |
| `Technical/DotnetString::trim` | `String.Trim()` whitespace set (`Char.IsWhiteSpace`) | `trim()` strips `\0` and keeps `\f`, NBSP, … |
| `Technical/DotnetString::replace` | `String.Replace` **throws** on an empty search string | `str_replace` silently does nothing |
| `Technical/DotnetString::tryParseInt` | `int.TryParse`: whole string, Int32 range | `(int)"3x"` is `3`, never fails |
| `Technical/DotnetString::split`, `indexOf`, `toString` | `Split()`, `IndexOf` → `-1`, `ToString()` (`True`/`False`) | different separators, `false`, `"1"`/`""` |
| `Technical/DotnetString::toLower`, `toUpper` | simple 1:1 case mapping (`İ` → `i`) | `mb_strtolower` full mapping (`İ` → `i̇`) breaks command matching |
| `Technical/DotnetConsole` | `Console.ReadLine`: `\r\n`, `\r`, `\n` endings; invalid UTF-8 → U+FFFD | `fgets` splits on `\n` only |
| `Technical/RanGens/DotnetRandom` | `System.Random`: seeded generator, `Next(min, max)` semantics | `random_int` is unseeded, with an inclusive max |
| `Technical/NotImplementedException` | `System.NotImplementedException` | no built-in |

One private stand-in: `QueryGameState::asBool()` reproduces C#'s `(bool)` unboxing cast inside an `if` (throws on
null or non-bool, where PHP's `(bool)` would coerce silently).

## Notable faithful choices (do not "fix" these)

- `Card` has no value equality. The deck removes the drawn card **by identity** (strict `array_search`). A
  loose `array_search` removes the wrong one of two equal cards.
- `GameState` extends `ArrayObject`: an insertion-ordered, **reference-typed** dictionary. A missing key returns
  `null`. A plain PHP array would be copied on every hand-off.
- `CardDeck::allCards()` and the `PlayedGameRules` list getters **return by reference**: the internal lists are
  exposed, as in C#.
- Every property is typed (and nullable where C# passes or tolerates null), so writing into a missing object
  crashes as the C# null dereference does, instead of PHP auto-creating an array.
- The parser keeps the dead-code trim, the `> 0` separator check, and replace-all parameter extraction.
- The REPL crashes wherever the C# REPL crashes (e.g. `"Guess 2C; "` with a trailing space, a blank line, a
  lowercase `exit`). The crash text goes to stderr. Exit code: .NET 134, PHP 255.
- 25 deliberate warts in total; see the behaviour analysis in the Python task folder
  (`_applications/_tasks/260616-01-python-version/03-claude-analysis-exact-behavior.md`).

## Known divergences from C# (accepted)

- **Regex word characters** (`\w`, `\b`) in card and command parsing: PCRE counts `\p{N}` and `_` as word
  characters; .NET counts `\p{Mn}`, `\p{Nd}` and `\p{Pc}`, and treats ZWJ/ZWNJ (U+200C/U+200D) as word
  characters for `\b`. This only matters for input containing `½`, superscripts, combining marks, `‿` or zero-width
  joiners. The regex text is kept identical to the C# source.
- **A separator immediately followed by a combining mark** (e.g. `;` + U+0301): .NET's culture-sensitive
  `IndexOf` (ICU) does not match it there; PHP is ordinal. C# itself behaves ordinally under
  `DOTNET_SYSTEM_GLOBALIZATION_INVARIANT=1`, so C#'s own behaviour depends on the environment.
- Code points vs UTF-16 code units: affects only exception messages for astral characters (emoji).
- Exception class names and stack traces (stderr only).

## Differential oracle

`scripts/differential_oracle.sh` builds the C# REPL if needed (`netcoreapp3.1`, run with
`DOTNET_ROLL_FORWARD=Major` on newer SDKs), feeds 30 transcripts to both programs, and requires identical stdout
plus matching success/crash. It covers playing, parsing, line endings, whitespace, Unicode and 12 crash paths. The
deck line is masked only where it's random (decks of 3+ cards after a draw).

Note: the Python and C++ ports diverge from C# on two inputs that this port matches (a whitespace-only order
record such as `"Guess 2C; "`, and `SetMaxTurns 1_0`). Diff against the C# binary, not against those ports.

**Not committed** by design: review and commit at your discretion.
