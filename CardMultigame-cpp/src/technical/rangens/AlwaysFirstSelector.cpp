#include "technical/rangens/AlwaysFirstSelector.hpp"

namespace cardmultigame::technical::rangens
{
    std::shared_ptr<entities::cards::Card> AlwaysFirstSelector::DrawCard(const std::vector<std::shared_ptr<entities::cards::Card>>& cards)
    {
        return cards[0];
    }
}
