#include "usecases/cardcomparison/AlwaysFailComparisonStrategy.hpp"

namespace cardmultigame::usecases::cardcomparison
{
    bool AlwaysFailComparisonStrategy::AreTheSame(const std::shared_ptr<entities::cards::Card>&,
                                                  const std::shared_ptr<entities::cards::Card>&)
    {
        return false;
    }
}
