<?php

declare(strict_types=1);

namespace CardMultigame\Technical;

/**
 * Non-mirror helper: .NET System.NotImplementedException has no PHP built-in counterpart.
 */
class NotImplementedException extends \LogicException
{
    public function __construct(string $message = 'The method or operation is not implemented.')
    {
        parent::__construct($message);
    }
}
