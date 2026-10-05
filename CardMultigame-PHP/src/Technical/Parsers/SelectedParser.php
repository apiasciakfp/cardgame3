<?php

declare(strict_types=1);

namespace CardMultigame\Technical\Parsers;

use CardMultigame\Technical\DotnetString;
use CardMultigame\Technical\Parsers\ParseStrategies\CommaParseStrategy;
use CardMultigame\Technical\Parsers\ParseStrategies\DashParseStrategy;
use CardMultigame\Technical\Parsers\ParseStrategies\IParseStrategy;
use CardMultigame\Technical\Parsers\ParseStrategies\SemicolonParseStrategy;

class SelectedParser
{
    /** @var list<IParseStrategy> */
    private array $parseStrategies;

    public function __construct()
    {
        $this->parseStrategies = $this->registerPossibleStrategies();
    }

    /**
     * @return list<array{0: string, 1: string}>
     */
    public function properlyParse(string $orderString): array
    {
        $selectedStrategy = $this->selectAppropriateStrategy($orderString);

        if ($selectedStrategy === null) throw new \InvalidArgumentException('Order string is wrong or appropriate parsing Strategy is not registered');

        $result = (new PerformParsing($selectedStrategy))->executeOn($orderString);
        return $result;
    }

    private function selectAppropriateStrategy(string $orderString): ?IParseStrategy
    {
        $lastPostition = PHP_INT_MAX;
        $selectedStrategy = null;
        foreach ($this->parseStrategies as $strategy) {
            $potential = $strategy->separator();

            $currentPosition = DotnetString::indexOf($orderString, $potential);
            if ($currentPosition > 0 && $currentPosition < $lastPostition) {
                $selectedStrategy = $strategy;
                $lastPostition = $currentPosition;
            }
        }

        return $selectedStrategy;
    }

    /**
     * @return list<IParseStrategy>
     */
    private function registerPossibleStrategies(): array
    {
        $registeredStrategies = [
            new CommaParseStrategy(),
            new SemicolonParseStrategy(),
            new DashParseStrategy(),
        ];

        return $registeredStrategies;
    }
}
