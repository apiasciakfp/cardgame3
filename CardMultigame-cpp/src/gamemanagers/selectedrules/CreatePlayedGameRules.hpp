#pragma once

#include "gamemanagers/selectedrules/PlayedGameRules.hpp"
#include "usecases/cardcomparison/ICardComparisonStrategy.hpp"
#include "usecases/gameactions/IGameAction.hpp"
#include "usecases/gameconditions/IGameCondition.hpp"

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace cardmultigame::gamemanagers::selectedrules
{
    class CreatePlayedGameRules
    {
        using ActionList = std::vector<std::shared_ptr<usecases::gameactions::IGameAction>>;
        using ConditionList = std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>>;
        using Comparator = std::shared_ptr<usecases::cardcomparison::ICardComparisonStrategy>;

    public:
        std::shared_ptr<PlayedGameRules> Empty();

        // Nullable overrides: an empty optional / null comparator keeps the default (mirrors the
        // C# `if (x != null)` guards).
        std::shared_ptr<PlayedGameRules> WithModifications(const std::optional<std::string>& gameName,
                                                           const std::optional<ActionList>& actions,
                                                           const std::optional<ConditionList>& victories,
                                                           const std::optional<ConditionList>& gameStops,
                                                           const Comparator& compareCards);
    };
}
