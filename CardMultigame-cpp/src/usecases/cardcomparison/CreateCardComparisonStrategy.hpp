#pragma once

#include "usecases/cardcomparison/ICardComparisonStrategy.hpp"

#include <memory>
#include <string>

namespace cardmultigame::usecases::cardcomparison
{
    class CreateCardComparisonStrategy
    {
    public:
        std::shared_ptr<ICardComparisonStrategy> Create(const std::string& selector);
        std::shared_ptr<ICardComparisonStrategy> None();
    };
}
