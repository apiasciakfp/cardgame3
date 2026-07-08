#include "technical/rangens/AlwaysLastSelector.hpp"

namespace cardmultigame::technical::rangens
{
    std::shared_ptr<entities::cards::Card> AlwaysLastSelector::DrawCard(const std::vector<std::shared_ptr<entities::cards::Card>>& cards)
    {
        return cards[cards.size() - 1];
    }
}
