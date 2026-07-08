#pragma once

#include "entities/cards/Card.hpp"

#include <memory>

namespace cardmultigame::usecases::cardcomparison
{
    class ICardComparisonStrategy
    {
    public:
        virtual ~ICardComparisonStrategy() = default;

        virtual bool AreTheSame(const std::shared_ptr<entities::cards::Card>& card1,
                                const std::shared_ptr<entities::cards::Card>& card2) = 0;
    };
}
