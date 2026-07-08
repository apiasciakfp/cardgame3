#include "technical/parsers/PerformParsing.hpp"

#include "technical/StringUtils.hpp"

#include <regex>

namespace cardmultigame::technical::parsers
{
    PerformParsing::PerformParsing(std::shared_ptr<parsestrategies::IParseStrategy> parseStrategy)
        : _parseStrategy(std::move(parseStrategy))
    {
    }

    std::vector<std::pair<std::string, std::string>> PerformParsing::ExecuteOn(const std::string& orderString) const
    {
        std::vector<std::string> records = _parseStrategy->SplitIntoRecords(orderString);

        const std::string singleFirstWord = R"((\b\w+\b){1})";

        std::vector<std::pair<std::string, std::string>> actionsWithParams;
        for (const std::string& record : records)
        {
            std::regex regexObj(singleFirstWord, std::regex::ECMAScript | std::regex::multiline);
            std::smatch actionSigilMatch;

            std::string actionSigil = std::regex_search(record, actionSigilMatch, regexObj)
                                          ? actionSigilMatch.str()
                                          : "";
            std::string paramsSigil = ReplaceAll(record, actionSigil, "");

            actionsWithParams.emplace_back(Trim(actionSigil), Trim(paramsSigil));
        }

        return actionsWithParams;
    }
}
