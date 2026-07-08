#pragma once

#include "entities/cards/Card.hpp"

#include <memory>
#include <string>
#include <vector>

namespace cardmultigame::entities::cards
{
    class CreateCards
    {
    public:
        virtual ~CreateCards() = default;

        virtual std::vector<std::shared_ptr<Card>> CreateCollection(const std::string& cardStrings);
        virtual std::shared_ptr<Card> CreateSingle(const std::string& prototype);

    private:
        std::string ExtractColour(const std::string& prototype);
        std::string ExtractRank(const std::string& prototype);
        std::shared_ptr<Card> DamagedCard();
        bool IsValidCardPrototype(const std::string& prototype);
    };
}
