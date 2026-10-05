<?php

declare(strict_types=1);

namespace CardMultigame\Usecases\GameActions;

use CardMultigame\Technical\DotnetString;

class CreateGameActions
{
    /**
     * @return list<IGameAction>
     */
    public function havingOrders(string $actionsToPerform): array
    {
        $tokens = DotnetString::split($actionsToPerform);
        $actions = [];
        foreach ($tokens as $token) {
            $sanitized = trim($token, ',');
            if ($sanitized === 'drawSingleCard') $actions[] = new DrawSingleCardAction();
            if ($sanitized === 'addQH') $actions[] = new AddQueenOfHeartsToDeck();
            if ($sanitized === 'add10cOrDraw') $actions[] = new Add10COrDrawACard();
        }

        return $actions;
    }
}
