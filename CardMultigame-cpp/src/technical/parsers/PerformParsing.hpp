#pragma once

#include "technical/parsers/parsestrategies/IParseStrategy.hpp"

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace cardmultigame::technical::parsers
{
    class PerformParsing
    {
        std::shared_ptr<parsestrategies::IParseStrategy> _parseStrategy;

    public:
        explicit PerformParsing(std::shared_ptr<parsestrategies::IParseStrategy> parseStrategy);

        std::vector<std::pair<std::string, std::string>> ExecuteOn(const std::string& orderString) const;
    };
}
