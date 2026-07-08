#pragma once

#include "technical/rangens/ICardSelector.hpp"

namespace cardmultigame::technical::rangens
{
    class AlwaysFirstSelector : public ICardSelector
    {
    public:
        std::shared_ptr<entities::cards::Card> DrawCard(const std::vector<std::shared_ptr<entities::cards::Card>>& cards) override;
    };
}
