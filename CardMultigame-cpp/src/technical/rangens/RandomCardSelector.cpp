#include "technical/rangens/RandomCardSelector.hpp"

namespace cardmultigame::technical::rangens
{
    std::shared_ptr<entities::cards::Card> RandomCardSelector::DrawCard(const std::vector<std::shared_ptr<entities::cards::Card>>& cards)
    {
        // Next(0, count-1): max is exclusive, so for count>=2 the last card is never drawn (WART-13).
        const int index = _random.Next(0, static_cast<int>(cards.size()) - 1);
        return cards[index];
    }
}
