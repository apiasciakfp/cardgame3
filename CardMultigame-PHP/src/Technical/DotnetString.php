<?php

declare(strict_types=1);

namespace CardMultigame\Technical;

/**
 * Non-mirror helper: .NET string semantics that PHP's built-ins don't share.
 */
final class DotnetString
{
    /**
     * What .NET's object.ToString() prints for the values this app stores in a GameState
     * (via KeyValuePair.ToString(), where a null value prints as empty).
     * PHP would print true as "1" and false as "".
     */
    public static function toString(mixed $value): string
    {
        return match (true) {
            $value === null => '',
            is_bool($value) => $value ? 'True' : 'False',
            is_int($value) => (string) $value,
            is_string($value) => $value,
            $value instanceof \Stringable => (string) $value,
            default => throw new \LogicException('No .NET ToString() mapping for ' . get_debug_type($value)),
        };
    }

    /**
     * .NET Char.IsWhiteSpace: what String.Trim() strips. Not PHP trim()'s " \t\n\r\0\x0B"
     * (PHP strips \0 and keeps \f; .NET does the opposite, and also strips NBSP, U+0085, U+2028...).
     */
    private const WHITE_SPACE = '\x{0009}-\x{000D}\x{0020}\x{0085}\x{00A0}\x{1680}\x{2000}-\x{200A}\x{2028}\x{2029}\x{202F}\x{205F}\x{3000}';

    /**
     * .NET String.Trim().
     */
    public static function trim(string $value): string
    {
        return preg_replace('/\A[' . self::WHITE_SPACE . ']+|[' . self::WHITE_SPACE . ']+\z/u', '', $value);
    }

    /**
     * .NET String.ToLower(): SIMPLE (1:1) case mapping. mb_strtolower uses full mapping
     * ("İ" -> "i̇", two code points), which breaks the case-insensitive command match.
     */
    public static function toLower(string $value): string
    {
        return mb_convert_case($value, MB_CASE_LOWER_SIMPLE);
    }

    /**
     * .NET String.ToUpper(): SIMPLE (1:1) case mapping (mb_strtoupper would turn "ß" into "SS").
     */
    public static function toUpper(string $value): string
    {
        return mb_convert_case($value, MB_CASE_UPPER_SIMPLE);
    }

    /**
     * .NET String.Split() with no arguments: every Char.IsWhiteSpace character is a separator,
     * empty entries are kept ("a  b" -> ["a", "", "b"]; "" -> [""]).
     *
     * @return list<string>
     */
    public static function split(string $value): array
    {
        return preg_split('/[' . self::WHITE_SPACE . ']/u', $value);
    }

    /**
     * .NET String.Replace(oldValue, newValue): ordinal, replaces EVERY occurrence, and throws on an
     * empty oldValue (PHP's str_replace silently returns the subject unchanged).
     */
    public static function replace(string $value, string $oldValue, string $newValue): string
    {
        if ($oldValue === '') {
            throw new \InvalidArgumentException("The value cannot be an empty string. (Parameter 'oldValue')");
        }

        return str_replace($oldValue, $newValue, $value);
    }

    /**
     * .NET String.IndexOf(value): -1 when absent (PHP returns false). Character index, not byte offset.
     */
    public static function indexOf(string $value, string $searched): int
    {
        $position = mb_strpos($value, $searched);
        return $position === false ? -1 : $position;
    }

    /**
     * .NET int.TryParse(s, out result) with NumberStyles.Integer: optional leading/trailing
     * \t \n \v \f \r and space (NOT the wider Trim() set), optional sign, ASCII digits only,
     * Int32 range, and trailing NULs tolerated at the very end. PHP's (int) cast never fails.
     */
    public static function tryParseInt(string $value, ?int &$result): bool
    {
        $result = 0;
        if (preg_match('/\A[\x09-\x0D\x20]*([+-]?)([0-9]+)[\x09-\x0D\x20]*\x00*\z/', $value, $parts) !== 1) {
            return false;
        }

        $digits = ltrim($parts[2], '0');
        if (strlen($digits) > 10) {
            return false;
        }

        $magnitude = $digits === '' ? 0 : (int) $digits;
        $parsed = $parts[1] === '-' ? -$magnitude : $magnitude;
        if ($parsed < -2147483648 || $parsed > 2147483647) {
            return false;
        }

        $result = $parsed;
        return true;
    }

    private function __construct()
    {
    }
}
