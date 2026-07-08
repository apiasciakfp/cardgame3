#pragma once

#include "technical/parsers/parsestrategies/IParseStrategy.hpp"

#include <string>
#include <vector>

namespace cardmultigame::technical::parsers::parsestrategies
{
    class CommaParseStrategy : public IParseStrategy
    {
        std::string _separator = ",";

    public:
        std::string Separator() const override;
        std::vector<std::string> SplitIntoRecords(const std::string& orderString) const override;
    };
}
