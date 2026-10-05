<?php

declare(strict_types=1);

namespace CardMultigame\Entities\GameStates;

/**
 * This is for readability ONLY. An example implementation of
 * EncapsulatedContext pattern is a Dictionary of this type
 * passed where needed.
 *
 * Do not do this in the real world systems unless you REALLY know
 * what you are doing.
 *
 * @extends \ArrayObject<string, mixed>
 */
class GameState extends \ArrayObject
{
    /**
     * This is done ONLY to make it much easier to work with for people
     * less accustomed to working with Dictionaries. In normal real world stuff do not do this.
     */
    public function offsetGet(mixed $key): mixed
    {
        if (parent::offsetExists($key)) {
            return parent::offsetGet($key);
        } else {
            return null;
        }
    }
}
