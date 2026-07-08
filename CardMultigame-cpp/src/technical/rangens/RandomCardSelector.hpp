#pragma once

#include "technical/rangens/DotnetRandom.hpp"
#include "technical/rangens/ICardSelector.hpp"

namespace cardmultigame::technical::rangens
{
    class RandomCardSelector : public ICardSelector
    {
        DotnetRandom _random; // seeded weakly at construction, mirroring `new Random(DateTime.Now.Millisecond)`

    public:
        std::shared_ptr<entities::cards::Card> DrawCard(const std::vector<std::shared_ptr<entities::cards::Card>>& cards) override;
    };
}
