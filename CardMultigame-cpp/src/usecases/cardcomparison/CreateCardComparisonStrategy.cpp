#include "usecases/cardcomparison/CreateCardComparisonStrategy.hpp"

#include "usecases/cardcomparison/AlwaysFailComparisonStrategy.hpp"
#include "usecases/cardcomparison/BlackRedColourOnlyComparisonStrategy.hpp"
#include "usecases/cardcomparison/ColourCardComparisonStrategy.hpp"
#include "usecases/cardcomparison/RankCardComparisonStrategy.hpp"
#include "usecases/cardcomparison/StrictCardComparisonStrategy.hpp"

namespace cardmultigame::usecases::cardcomparison
{
    std::shared_ptr<ICardComparisonStrategy> CreateCardComparisonStrategy::Create(const std::string& selector)
    {
        if (selector == "strict") return std::make_shared<StrictCardComparisonStrategy>();
        if (selector == "colour") return std::make_shared<ColourCardComparisonStrategy>();
        if (selector == "blackred") return std::make_shared<BlackRedColourOnlyComparisonStrategy>();
        if (selector == "rank") return std::make_shared<RankCardComparisonStrategy>();
        else return std::make_shared<AlwaysFailComparisonStrategy>();
    }

    std::shared_ptr<ICardComparisonStrategy> CreateCardComparisonStrategy::None()
    {
        return std::make_shared<AlwaysFailComparisonStrategy>();
    }
}
