#include "usecases/cardcomparison/BlackRedColourOnlyComparisonStrategy.hpp"

#include <map>
#include <string>

namespace cardmultigame::usecases::cardcomparison
{
    bool BlackRedColourOnlyComparisonStrategy::AreTheSame(const std::shared_ptr<entities::cards::Card>& card1,
                                                          const std::shared_ptr<entities::cards::Card>& card2)
    {
        const std::map<std::string, std::string> colourMap = {
            {"H", "red"},
            {"D", "red"},
            {"C", "black"},
            {"S", "black"},
        };

        const std::string card1Colour = colourMap.at(card1->Colour());
        const std::string card2Colour = colourMap.at(card2->Colour());

        if (card1Colour == card2Colour)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
