<?php

declare(strict_types=1);

namespace CardMultigame\Technical\Parsers;

use CardMultigame\Technical\DotnetString;
use CardMultigame\Technical\Parsers\ParseStrategies\IParseStrategy;

class PerformParsing
{
    private IParseStrategy $parseStrategy;

    public function __construct(IParseStrategy $parseStrategy)
    {
        $this->parseStrategy = $parseStrategy;
    }

    /**
     * C# List<Tuple<string, string>>: each order is an [action, params] pair (compares by value, like Tuple).
     *
     * @return list<array{0: string, 1: string}>
     */
    public function executeOn(string $orderString): array
    {
        $records = $this->parseStrategy->splitIntoRecords($orderString);

        $singleFirstWord = '/(\b\w+\b){1}/mu';

        $actionsWithParams = [];
        foreach ($records as $record) {
            preg_match($singleFirstWord, $record, $actionSigilMatch);

            $actionSigil = $actionSigilMatch[0] ?? '';
            $paramsSigil = DotnetString::replace($record, $actionSigil, '');

            $actionsWithParams[] = [DotnetString::trim($actionSigil), DotnetString::trim($paramsSigil)];
        }

        return $actionsWithParams;
    }
}
