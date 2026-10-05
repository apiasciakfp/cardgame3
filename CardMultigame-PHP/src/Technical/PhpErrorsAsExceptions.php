<?php

declare(strict_types=1);

namespace CardMultigame\Technical;

/**
 * Non-mirror helper (no C# counterpart).
 *
 * C# throws where PHP only warns: a missing Dictionary key (KeyNotFoundException),
 * an out-of-range List index, a null dereference. PHP emits a warning, returns null
 * and carries on, which would silently turn every C# crash into "the game continues".
 * Installed by bin/cardmultigame and by the test bootstrap, so both behave like C#.
 *
 * error_reporting(E_ALL) first: distro php.ini files often exclude E_DEPRECATED, and the
 * severity guard below would then let deprecations pass silently (it still honours `@`).
 */
final class PhpErrorsAsExceptions
{
    public static function install(): void
    {
        error_reporting(E_ALL);

        set_error_handler(static function (int $severity, string $message, string $file, int $line): bool {
            if ((error_reporting() & $severity) === 0) {
                return false;
            }

            throw new \ErrorException($message, 0, $severity, $file, $line);
        });
    }
}
