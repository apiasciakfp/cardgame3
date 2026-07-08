#include "usecases/cardcomparison/ColourCardComparisonStrategy.hpp"

namespace cardmultigame::usecases::cardcomparison
{
    bool ColourCardComparisonStrategy::AreTheSame(const std::shared_ptr<entities::cards::Card>& card1,
                                                  const std::shared_ptr<entities::cards::Card>& card2)
    {
        if (card1->Colour() == card2->Colour())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
