#pragma once

#include "technical/parsers/parsestrategies/IParseStrategy.hpp"

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace cardmultigame::technical::parsers
{
    class SelectedParser
    {
        std::vector<std::shared_ptr<parsestrategies::IParseStrategy>> _parseStrategies;

        std::shared_ptr<parsestrategies::IParseStrategy> SelectAppropriateStrategy(const std::string& orderString) const;
        static std::vector<std::shared_ptr<parsestrategies::IParseStrategy>> RegisterPossibleStrategies();

    public:
        SelectedParser();

        std::vector<std::pair<std::string, std::string>> ProperlyParse(const std::string& orderString) const;
    };
}
