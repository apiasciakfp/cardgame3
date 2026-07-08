#!/usr/bin/env bash
# Differential oracle (Slice 6, DA #9): feed identical REPL transcripts to the C++ port and the
# completed Python port (which is byte-identical to the real C# binary), then diff.
# The [CardDeck, Deck: ...] line is non-deterministic (RandomCardSelector, no injection point in the
# REPL) so it is MASKED before diffing — every other line is deterministic for out-of-deck guesses.
set -u

CPP_BIN="$(dirname "$0")/../build/cardmultigame"
PY_DIR="$(dirname "$0")/../../CardMultigame-Python"

mask() { sed -E 's/\[CardDeck, Deck:[^]]*\]/[CardDeck, <deck masked>]/'; }

run_case() {
    local name="$1" transcript="$2"
    local cpp py
    cpp="$(printf '%s' "$transcript" | "$CPP_BIN" | mask)"
    py="$(printf '%s' "$transcript" | (cd "$PY_DIR" && uv run --quiet cardmultigame 2>/dev/null) | mask)"
    if [ "$cpp" == "$py" ]; then
        echo "PASS  $name"
    else
        echo "FAIL  $name"
        diff <(printf '%s' "$cpp") <(printf '%s' "$py") | head -40
        return 1
    fi
}

fails=0
# Deterministic-outcome transcripts (out-of-deck guesses -> defeat; in-deck under BlackRed -> victory).
run_case "defeat_3turns"       "Play GuessACard; SetDeck JH,QH,KH; SetMaxTurns 3; SETUP
Guess 2C;
Guess 2C;
Guess 2C;
EXIT
" || fails=$((fails+1))

run_case "defeat_mixed_seps"   "Play GuessACard, SetDeck JH;QH;KH, SetMaxTurns 3, SETUP
Guess 2C,
Guess 2C,
Guess 2C,
EXIT
" || fails=$((fails+1))

run_case "redblack_victory"    "Play GuessACard; SetDeck JH,QH,KH; GameVariant RedBlack; SETUP
Guess 2C;
Guess 2C;
Guess 2D;
EXIT
" || fails=$((fails+1))

run_case "empty_setup_then_exit" "Play GuessACard; SetDeck JH,QH,KH; SetMaxTurns 5; SETUP
EXIT
" || fails=$((fails+1))

echo
if [ "$fails" -eq 0 ]; then echo "ALL DIFFERENTIAL CASES PASS (C++ == Python == C#)"; else echo "$fails case(s) FAILED"; fi
exit "$fails"
