#!/usr/bin/env bash
# Structural gates: greps for the PHP idioms that silently change C# behaviour.
# Each gate prints offending lines; any output = failure. See README "Faithful choices".
set -u
cd "$(dirname "$0")/.."

fails=0
gate() { # <name> <offending lines (empty = pass)>
    if [ -z "$2" ]; then printf 'PASS  %s\n' "$1"; else printf 'FAIL  %s\n%s\n' "$1" "$2"; fails=$((fails+1)); fi
}

gate "no loose == (use ===)"                    "$(grep -rnP '[^=!<>]==[^=]' src)"
gate "no loose != (use !==)"                    "$(grep -rnP '!=[^=]' src)"
gate "no switch (loose comparison; use match)"  "$(grep -rnP '\bswitch\s*\(' src)"
gate "in_array/array_search/array_keys strict"  "$(grep -rnP '\b(in_array|array_search|array_keys)\(' src | grep -v ', true)')"
gate "no unseeded RNG (use DotnetRandom)"       "$(grep -rnP '\b(random_int|mt_rand|rand|array_rand|shuffle)\(' src)"
gate "no (int)/intval outside DotnetString"     "$(grep -rnP '\(int\)|\bintval\(' src | grep -v '^src/Technical/DotnetString.php:' | grep -v "format('v')")"
gate "no native trim() (use DotnetString::trim)" "$(grep -rnP '(?<![\w:>])trim\(' src | grep -v '^src/Technical/DotnetString.php:' | grep -v "trim(\$token, ',')")"
gate "case mapping only via DotnetString (simple)" "$(grep -rnP '\b(mb_)?strto(lower|upper)\(' src | grep -v '^src/Technical/DotnetString.php:')"
gate "no fgets outside DotnetConsole"           "$(grep -rnP '\bfgets\(' src bin | grep -v '^src/Technical/DotnetConsole.php:')"
gate "no unset() on lists (keep indices dense)" "$(grep -rnP '\bunset\(' src)"
gate "every property typed"                     "$(grep -rnP '\b(private|protected|public)(\s+static)?(\s+readonly)?\s+\$' src)"
gate "strict_types in every PHP file"           "$(for f in $(find src tests -name '*.php') bin/cardmultigame; do grep -q 'declare(strict_types=1);' "$f" || echo "$f"; done)"

echo
if [ "$fails" -eq 0 ]; then echo "ALL GATES PASS"; else echo "$fails gate(s) FAILED"; fi
exit "$fails"
