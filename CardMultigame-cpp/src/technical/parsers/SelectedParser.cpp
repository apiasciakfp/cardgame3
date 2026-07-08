#include "technical/parsers/SelectedParser.hpp"

#include "technical/parsers/PerformParsing.hpp"
#include "technical/parsers/parsestrategies/CommaParseStrategy.hpp"
#include "technical/parsers/parsestrategies/DashParseStrategy.hpp"
#include "technical/parsers/parsestrategies/SemicolonParseStrategy.hpp"

#include <limits>
#include <stdexcept>

namespace cardmultigame::technical::parsers
{
    SelectedParser::SelectedParser()
        : _parseStrategies(RegisterPossibleStrategies())
    {
    }

    std::vector<std::pair<std::string, std::string>> SelectedParser::ProperlyParse(const std::string& orderString) const
    {
        std::shared_ptr<parsestrategies::IParseStrategy> selectedStrategy = SelectAppropriateStrategy(orderString);

        if (selectedStrategy == nullptr)
        {
            throw std::invalid_argument("Order string is wrong or appropriate parsing Strategy is not registered");
        }

        return PerformParsing(selectedStrategy).ExecuteOn(orderString);
    }

    std::shared_ptr<parsestrategies::IParseStrategy> SelectedParser::SelectAppropriateStrategy(const std::string& orderString) const
    {
        int lastPosition = std::numeric_limits<int>::max();
        std::shared_ptr<parsestrategies::IParseStrategy> selectedStrategy = nullptr;
        for (const auto& strategy : _parseStrategies)
        {
            std::string potential = strategy->Separator();

            const auto found = orderString.find(potential);
            const int currentPosition = (found == std::string::npos) ? -1 : static_cast<int>(found);
            if (currentPosition > 0 && currentPosition < lastPosition)
            {
                selectedStrategy = strategy;
                lastPosition = currentPosition;
            }
        }

        return selectedStrategy;
    }

    std::vector<std::shared_ptr<parsestrategies::IParseStrategy>> SelectedParser::RegisterPossibleStrategies()
    {
        return {
            std::make_shared<parsestrategies::CommaParseStrategy>(),
            std::make_shared<parsestrategies::SemicolonParseStrategy>(),
            std::make_shared<parsestrategies::DashParseStrategy>(),
        };
    }
}
