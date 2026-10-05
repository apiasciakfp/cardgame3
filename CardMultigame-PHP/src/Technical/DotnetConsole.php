<?php

declare(strict_types=1);

namespace CardMultigame\Technical;

/**
 * Non-mirror helper: the parts of .NET System.Console the REPL relies on.
 *
 * ReadLine() differs from fgets() in two ways that change behaviour:
 * - line terminators are "\r\n", a lone "\r", or "\n" (fgets only splits on "\n"),
 *   and the terminator is not part of the returned line;
 * - input is decoded as UTF-8 with invalid bytes replaced by U+FFFD (PHP would keep
 *   the raw bytes, and /u regexes would then fail on them).
 * It returns null at end of input, as C# does.
 */
final class DotnetConsole
{
    private static string $pending = '';

    public static function readLine(): ?string
    {
        while (true) {
            $terminator = strcspn(self::$pending, "\r\n");
            $atEnd = feof(STDIN);

            if ($terminator < strlen(self::$pending)) {
                $isCarriageReturn = self::$pending[$terminator] === "\r";
                if ($isCarriageReturn && $terminator === strlen(self::$pending) - 1 && !$atEnd) {
                    self::readMore(); // is it "\r\n" or a lone "\r"? Need the next byte to know.
                    continue;
                }

                $line = substr(self::$pending, 0, $terminator);
                $skip = ($isCarriageReturn && ($terminator + 1) < strlen(self::$pending) && self::$pending[$terminator + 1] === "\n") ? 2 : 1;
                self::$pending = substr(self::$pending, $terminator + $skip);
                return self::decode($line);
            }

            if ($atEnd || !self::readMore()) {
                if (self::$pending === '') {
                    return null;
                }

                $line = self::$pending;
                self::$pending = '';
                return self::decode($line);
            }
        }
    }

    public static function writeLine(string $value): void
    {
        echo $value . PHP_EOL;
    }

    public static function write(string $value): void
    {
        echo $value;
    }

    private static function readMore(): bool
    {
        $chunk = fgets(STDIN);
        if ($chunk === false) {
            return false;
        }

        self::$pending .= $chunk;
        return true;
    }

    private static function decode(string $line): string
    {
        $previous = mb_substitute_character();
        mb_substitute_character(0xFFFD);
        $decoded = mb_scrub($line, 'UTF-8');
        mb_substitute_character($previous);

        return $decoded;
    }

    private function __construct()
    {
    }
}
