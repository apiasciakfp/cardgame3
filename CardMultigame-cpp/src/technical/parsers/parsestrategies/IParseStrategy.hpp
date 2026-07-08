#pragma once

#include <string>
#include <vector>

namespace cardmultigame::technical::parsers::parsestrategies
{
    class IParseStrategy
    {
    public:
        virtual ~IParseStrategy() = default;

        virtual std::string Separator() const = 0;
        virtual std::vector<std::string> SplitIntoRecords(const std::string& orderString) const = 0;
    };
}
