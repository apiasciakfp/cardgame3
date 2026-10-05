<?php

declare(strict_types=1);

namespace CardMultigame\Technical\Parsers\ParseStrategies;

interface IParseStrategy
{
    public function separator(): string;

    /**
     * @return list<string>
     */
    public function splitIntoRecords(string $orderString): array;
}
