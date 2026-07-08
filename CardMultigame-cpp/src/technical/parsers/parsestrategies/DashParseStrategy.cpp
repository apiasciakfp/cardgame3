#include "technical/parsers/parsestrategies/DashParseStrategy.hpp"

#include "technical/StringUtils.hpp"

namespace cardmultigame::technical::parsers::parsestrategies
{
    std::string DashParseStrategy::Separator() const
    {
        return _separator;
    }

    std::vector<std::string> DashParseStrategy::SplitIntoRecords(const std::string& orderString) const
    {
        auto records = SplitKeepEmpty(orderString, _separator);

        std::vector<std::string> sanitizedRecords;
        for (const auto& record : records)
        {
            if (!record.empty())
            {
                auto sanitized = Trim(record); // WART-9: computed then discarded (dead-code trim)
                (void)sanitized;
                if (!record.empty())
                {
                    sanitizedRecords.push_back(record); // the UNtrimmed record
                }
            }
        }

        return sanitizedRecords;
    }
}
