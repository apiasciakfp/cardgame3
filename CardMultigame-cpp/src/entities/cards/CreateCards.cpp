#include "entities/cards/CreateCards.hpp"

#include <cctype>
#include <regex>
#include <stdexcept>

namespace cardmultigame::entities::cards
{
    std::vector<std::shared_ptr<Card>> CreateCards::CreateCollection(const std::string& cardStrings)
    {
        const std::string cardPrototypePattern = R"(((\b\w{2,3}\b)+))";

        std::regex regexObj(cardPrototypePattern, std::regex::ECMAScript | std::regex::multiline);

        std::vector<std::shared_ptr<Card>> cards;
        auto begin = std::sregex_iterator(cardStrings.begin(), cardStrings.end(), regexObj);
        auto end = std::sregex_iterator();
        for (auto it = begin; it != end; ++it)
        {
            std::string prototype = it->str();
            if (IsValidCardPrototype(prototype))
            {
                cards.push_back(CreateSingle(prototype));
            }
        }

        return cards;
    }

    std::shared_ptr<Card> CreateCards::CreateSingle(const std::string& prototype)
    {
        if (IsValidCardPrototype(prototype) == false)
        {
            return DamagedCard();
        }

        std::string rank = ExtractRank(prototype);
        std::string colour = ExtractColour(prototype);

        return std::make_shared<Card>(rank, colour);
    }

    std::string CreateCards::ExtractColour(const std::string& prototype)
    {
        std::string colourSign = prototype.substr(prototype.length() - 1);
        const char upper = static_cast<char>(std::toupper(static_cast<unsigned char>(colourSign[0])));

        if (upper == 'S') return "S";
        if (upper == 'H') return "H";
        if (upper == 'D') return "D";
        if (upper == 'C') return "C";

        throw std::invalid_argument("Colour extraction failed. Instead of SHDC we got: " + colourSign);
    }

    std::string CreateCards::ExtractRank(const std::string& prototype)
    {
        return prototype.substr(0, prototype.length() - 1);
    }

    std::shared_ptr<Card> CreateCards::DamagedCard()
    {
        return std::make_shared<Card>("Damaged", "Damaged");
    }

    bool CreateCards::IsValidCardPrototype(const std::string& prototype)
    {
        const std::string exactCardPrototypePattern = R"(\b(10[shdcSHDC]|[2-9jqkaJQKA][shdcSHDC])\b)";
        std::regex regexObj(exactCardPrototypePattern, std::regex::ECMAScript | std::regex::multiline);
        std::smatch cardPrototypes;

        if (std::regex_search(prototype, cardPrototypes, regexObj) && !cardPrototypes.str().empty())
        {
            return true;
        }

        return false;
    }
}
