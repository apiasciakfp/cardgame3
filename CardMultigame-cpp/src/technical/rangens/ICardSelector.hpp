#pragma once

#include "entities/cards/Card.hpp"

#include <memory>
#include <vector>

namespace cardmultigame::technical::rangens
{
    class ICardSelector
    {
    public:
        virtual ~ICardSelector() = default;

        virtual std::shared_ptr<entities::cards::Card> DrawCard(const std::vector<std::shared_ptr<entities::cards::Card>>& cards) = 0;
    };
}
