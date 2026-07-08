#include "usecases/cardcomparison/RankCardComparisonStrategy.hpp"

namespace cardmultigame::usecases::cardcomparison
{
    bool RankCardComparisonStrategy::AreTheSame(const std::shared_ptr<entities::cards::Card>& card1,
                                                const std::shared_ptr<entities::cards::Card>& card2)
    {
        if (card1->Rank() == card2->Rank())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
