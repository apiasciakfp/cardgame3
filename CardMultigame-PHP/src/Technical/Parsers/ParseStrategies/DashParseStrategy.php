<?php

declare(strict_types=1);

namespace CardMultigame\Technical\Parsers\ParseStrategies;

use CardMultigame\Technical\DotnetString;

class DashParseStrategy implements IParseStrategy
{
    private string $separator = '-';

    public function separator(): string
    {
        return $this->separator;
    }

    public function splitIntoRecords(string $orderString): array
    {
        $records = explode($this->separator, $orderString);

        $sanitizedRecords = [];
        foreach ($records as $record) {
            if ($record !== '') {
                $sanitized = DotnetString::trim($record);
                if ($record !== '') {
                    $sanitizedRecords[] = $record;
                }
            }
        }

        return $sanitizedRecords;
    }
}
