#pragma once

#include <string_view>

namespace cardmultigame::entities::gamestates
{
    // constexpr string_view constants — no static-init-order fragility across TUs (DA #8c).
    struct GameStateKeys
    {
        static constexpr std::string_view CurrentTurn = "CurrentTurnNumber";
        static constexpr std::string_view MaxTurns = "MaximumTurns";
        static constexpr std::string_view IsGameWon = "IsGameFinishedWithVictory";
        static constexpr std::string_view IsGameLost = "IsGameFinishedWithDefeat";
        static constexpr std::string_view CardDeck = "CardDeck";
    };
}
