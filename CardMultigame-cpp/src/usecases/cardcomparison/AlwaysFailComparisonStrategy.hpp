#pragma once

#include "usecases/cardcomparison/ICardComparisonStrategy.hpp"

namespace cardmultigame::usecases::cardcomparison
{
    // NullObject: always returns false.
    class AlwaysFailComparisonStrategy : public ICardComparisonStrategy
    {
    public:
        bool AreTheSame(const std::shared_ptr<entities::cards::Card>& card1,
                        const std::shared_ptr<entities::cards::Card>& card2) override;
    };
}
