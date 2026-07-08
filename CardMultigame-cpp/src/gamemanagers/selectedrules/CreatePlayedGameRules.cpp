#include "gamemanagers/selectedrules/CreatePlayedGameRules.hpp"

#include "usecases/cardcomparison/CreateCardComparisonStrategy.hpp"

namespace cardmultigame::gamemanagers::selectedrules
{
    std::shared_ptr<PlayedGameRules> CreatePlayedGameRules::Empty()
    {
        return std::make_shared<PlayedGameRules>(
            "No game selected",
            ActionList{},
            ConditionList{},
            ConditionList{},
            usecases::cardcomparison::CreateCardComparisonStrategy().None());
    }

    std::shared_ptr<PlayedGameRules> CreatePlayedGameRules::WithModifications(const std::optional<std::string>& gameName,
                                                                             const std::optional<ActionList>& actions,
                                                                             const std::optional<ConditionList>& victories,
                                                                             const std::optional<ConditionList>& gameStops,
                                                                             const Comparator& compareCards)
    {
        std::string selectedName = "No game selected";
        ActionList selectedActions{};
        ConditionList selectedVictories{};
        ConditionList selectedGameStops{};
        Comparator selectedCardComparators = usecases::cardcomparison::CreateCardComparisonStrategy().None();

        if (gameName.has_value()) selectedName = *gameName;
        if (actions.has_value()) selectedActions = *actions;
        if (victories.has_value()) selectedVictories = *victories;
        if (gameStops.has_value()) selectedGameStops = *gameStops;
        if (compareCards != nullptr) selectedCardComparators = compareCards;

        return std::make_shared<PlayedGameRules>(selectedName, selectedActions, selectedVictories, selectedGameStops, selectedCardComparators);
    }
}
