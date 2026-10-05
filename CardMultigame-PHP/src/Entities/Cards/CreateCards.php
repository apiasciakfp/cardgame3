<?php

declare(strict_types=1);

namespace CardMultigame\Entities\Cards;

use CardMultigame\Technical\DotnetString;

class CreateCards
{
    /**
     * @return list<Card>
     */
    public function createCollection(string $cardStrings): array
    {
        $cardPrototypePattern = '/((\b\w{2,3}\b)+)/mu';

        preg_match_all($cardPrototypePattern, $cardStrings, $cardPrototypes);

        $cards = [];
        foreach ($cardPrototypes[0] as $cardPrototypeMatch) {
            $prototype = $cardPrototypeMatch;
            if ($this->isValidCardPrototype($prototype)) {
                $cards[] = $this->createSingle($prototype);
            }
        }

        return $cards;
    }

    public function createSingle(string $prototype): Card
    {
        if ($this->isValidCardPrototype($prototype) === false) {
            return $this->damagedCard();
        }

        $rank = $this->extractRank($prototype);
        $colour = $this->extractColour($prototype);

        return new Card($rank, $colour);
    }

    private function extractColour(string $prototype): string
    {
        $colourSign = mb_substr($prototype, mb_strlen($prototype) - 1);

        if (DotnetString::toUpper($colourSign) === 'S') return 'S';
        if (DotnetString::toUpper($colourSign) === 'H') return 'H';
        if (DotnetString::toUpper($colourSign) === 'D') return 'D';
        if (DotnetString::toUpper($colourSign) === 'C') return 'C';

        throw new \InvalidArgumentException('Colour extraction failed. Instead of SHDC we got: ' . $colourSign);
    }

    private function extractRank(string $prototype): string
    {
        $rankSign = mb_substr($prototype, 0, mb_strlen($prototype) - 1);
        return $rankSign;
    }

    private function damagedCard(): Card
    {
        return new Card('Damaged', 'Damaged');
    }

    private function isValidCardPrototype(string $prototype): bool
    {
        $exactCardPrototypePattern = '/\b(10[shdcSHDC]|[2-9jqkaJQKA][shdcSHDC])\b/mu';
        preg_match($exactCardPrototypePattern, $prototype, $cardPrototypes);

        if (($cardPrototypes[0] ?? '') !== '') {
            return true;
        }

        return false;
    }
}
