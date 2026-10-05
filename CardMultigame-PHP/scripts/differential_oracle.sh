#!/usr/bin/env bash
# Differential oracle: feed identical REPL transcripts to the PHP port and the REAL C# binary, then compare.
#
# - stdout must be byte-identical, and both processes must agree on success (exit 0) vs crash (non-zero).
#   Exit codes are not compared literally: .NET crashes with 134, PHP with 255. Crash text goes to stderr
#   in both, and is not compared.
# - The [CardDeck, Deck: ...] line is masked only where it is non-deterministic: decks of 3+ cards after a
#   random draw (RandomCardSelector has no injection point in the REPL). Decks of 1-2 cards are deterministic.
# - Transcripts are printf %b escape strings, so \r, \0 and \xHH bytes reach both programs unchanged.
#
# Needs: php 8.3, dotnet SDK (C# targets netcoreapp3.1 -> runs with DOTNET_ROLL_FORWARD=Major).
set -u

HERE="$(cd "$(dirname "$0")" && pwd)"
PHP_BIN="$HERE/../bin/cardmultigame"
CS_PROJ="$HERE/../../CardMultigame/CardMultigame/CardMultigame.csproj"
CS_DLL="$HERE/../../CardMultigame/CardMultigame/bin/Debug/netcoreapp3.1/CardMultigame.dll"
export DOTNET_ROLL_FORWARD=Major

if [ ! -f "$CS_DLL" ]; then
    dotnet build "$CS_PROJ" -nologo -v q >/dev/null || { echo "C# build failed"; exit 2; }
fi

mask() { sed -E 's/\[CardDeck, Deck:[^]]*\]/[CardDeck, <deck masked>]/'; }

fails=0
# run_case <name> <ok|crash> <mask|exact> <transcript as printf %b string>
run_case() {
    local name="$1" expect="$2" masking="$3" transcript="$4"
    local cs php cs_rc php_rc
    cs="$(printf '%b' "$transcript" | dotnet "$CS_DLL" 2>/dev/null)"; cs_rc=$?
    php="$(printf '%b' "$transcript" | php "$PHP_BIN" 2>/dev/null)"; php_rc=$?
    if [ "$masking" = mask ]; then cs="$(printf '%s' "$cs" | mask)"; php="$(printf '%s' "$php" | mask)"; fi

    local outcome_ok=1
    if [ "$expect" = ok ]; then [ $cs_rc -eq 0 ] && [ $php_rc -eq 0 ] || outcome_ok=0
    else [ $cs_rc -ne 0 ] && [ $php_rc -ne 0 ] || outcome_ok=0; fi

    if [ "$cs" == "$php" ] && [ $outcome_ok -eq 1 ]; then
        printf 'PASS  %-28s (%s, C# rc=%s, PHP rc=%s)\n' "$name" "$expect" "$cs_rc" "$php_rc"
    else
        printf 'FAIL  %-28s (expected %s, C# rc=%s, PHP rc=%s)\n' "$name" "$expect" "$cs_rc" "$php_rc"
        diff <(printf '%s' "$cs") <(printf '%s' "$php") | head -20
        fails=$((fails+1))
    fi
}

# --- playing the game
run_case defeat_3turns            ok    mask  'Play GuessACard; SetDeck JH,QH,KH; SetMaxTurns 3; SETUP\nGuess 2C;\nGuess 2C;\nGuess 2C;\nEXIT\n'
run_case defeat_mixed_seps        ok    mask  'Play GuessACard, SetDeck JH;QH;KH, SetMaxTurns 3, SETUP\nGuess 2C,\nGuess 2C,\nGuess 2C,\nEXIT\n'
run_case redblack_victory         ok    mask  'Play GuessACard; SetDeck JH,QH,KH; GameVariant RedBlack; SETUP\nGuess 2C;\nGuess 2C;\nGuess 2D;\nEXIT\n'
run_case setup_then_exit          ok    exact 'Play GuessACard; SetDeck JH,QH,KH; SetMaxTurns 5; SETUP\nEXIT\n'
run_case two_card_deck            ok    exact 'Play GuessACard; SetDeck 2C,3C; SETUP\nGuess 3C;\nGuess 3C;\nEXIT\n'
run_case multiline_setup          ok    exact 'Play GuessACard;\nSetDeck 2C,3C;\nSETUP\nEXIT\n'
run_case orders_after_finish      ok    exact 'Play GuessACard; SetDeck 2C,3C; SetMaxTurns 1; SETUP\nGuess 9H;\nGuess 3C;\nEXIT\n'
# --- SetMaxTurns parsing (.NET int.TryParse)
run_case maxturns_007             ok    exact 'Play GuessACard; SetDeck 2C,3C; SetMaxTurns 007; SETUP\nEXIT\n'
run_case maxturns_1_0             ok    exact 'Play GuessACard; SetDeck 2C,3C; SetMaxTurns 1_0; SETUP\nEXIT\n'
run_case maxturns_trailing_nul    ok    exact 'Play GuessACard; SetDeck 2C,3C; SetMaxTurns 7\0; SETUP\nEXIT\n'
run_case maxturns_overflow        ok    exact 'Play GuessACard; SetDeck 2C,3C; SetMaxTurns 2147483648; SETUP\nEXIT\n'
# --- line endings (.NET Console.ReadLine)
run_case crlf_transcript          ok    exact 'Play GuessACard; SetDeck 2C,3C; SETUP\r\nGuess 3C;\r\nEXIT\r\n'
run_case lone_cr_midline          ok    exact 'Play GuessACard; SetDeck 2C,3C; SETUP\rGuess 3C;\nEXIT\n'
# --- whitespace (.NET String.Trim)
run_case formfeed_trim            ok    exact 'Play GuessACard; SetDeck 2C,3C; SETUP\nGuess 3C\f;\nEXIT\n'
run_case nbsp_trim                ok    exact 'Play GuessACard; SetDeck 2C,3C; SETUP\nGuess 3C\xc2\xa0;\nEXIT\n'
# --- Unicode handling that IS mirrored
run_case kelvin_sign_lowercase    ok    exact 'Play GuessACard; SetDec\xe2\x84\xaa 2C,3C; SETUP\nEXIT\n'
run_case invalid_utf8_input       ok    exact 'Play GuessACard; SetDeck 2C,3C\xff; SETUP\nEXIT\n'
run_case dotted_capital_i         ok    exact 'Play GuessACard; SetDeck 2H,3H; GameVar\xc4\xb0ant x; SETUP\nGuess 2D;\nEXIT\n'
# --- crashes: C# throws, so the PHP port must crash too
run_case trailing_space_crash     crash exact 'Play GuessACard; SetDeck 2C,3C; SETUP\nGuess 2C; \nEXIT\n'
run_case blackred_damaged_crash   crash exact 'Play GuessACard; SetDeck JH,QH,KH; GameVariant x; SETUP\nGuess zz;\nEXIT\n'
run_case guess_on_empty_deck      crash exact 'Play GuessACard; SetDeck 2C; SetMaxTurns 9; SETUP\nGuess 3C;\nGuess 3C;\nEXIT\n'
run_case nul_in_card_crash        crash exact 'Play GuessACard; SetDeck 2C,3C; SETUP\nGuess 3C\0;\nEXIT\n'
run_case blank_line_crash         crash exact 'Play GuessACard; SetDeck 2C,3C; SETUP\n\nEXIT\n'
run_case bare_setup_crash         crash exact 'SETUP\n'
run_case no_separator_crash       crash exact 'Play GuessACard\nSetDeck 2C,3C; SETUP\nEXIT\n'
run_case lowercase_exit_crash     crash exact 'Play GuessACard; SetDeck 2C,3C; SETUP\nexit\n'
run_case unknown_game_crash       crash exact 'Play Poker; SETUP\nEXIT\n'
run_case maxturns_before_play     crash exact 'SetMaxTurns 3; Play GuessACard; SETUP\nEXIT\n'
run_case resetup_after_maxturns   crash exact 'Play GuessACard; SetDeck 2C,3C; SETUP\nSetMaxTurns 9;\nSETUP\nEXIT\n'
run_case eof_without_exit         crash exact 'Play GuessACard; SetDeck 2C,3C; SETUP\n'

echo
if [ "$fails" -eq 0 ]; then echo "ALL DIFFERENTIAL CASES PASS (PHP == C#)"; else echo "$fails case(s) FAILED"; fi
exit "$fails"
