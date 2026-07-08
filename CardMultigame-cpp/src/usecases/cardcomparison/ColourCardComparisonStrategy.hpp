#pragma once

#include "usecases/cardcomparison/ICardComparisonStrategy.hpp"

namespace cardmultigame::usecases::cardcomparison
{
    class ColourCardComparisonStrategy : public ICardComparisonStrategy
    {
    public:
        bool AreTheSame(const std::shared_ptr<entities::cards::Card>& card1,
                        const std::shared_ptr<entities::cards::Card>& card2) override;
    };
}
