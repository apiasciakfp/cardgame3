#include "entities/cards/Card.hpp"

namespace cardmultigame::entities::cards
{
    Card::Card(std::string rank, std::string colour)
        : _rank(std::move(rank)), _colour(std::move(colour))
    {
    }

    std::string Card::Rank() const
    {
        return _rank;
    }

    std::string Card::Colour() const
    {
        return _colour;
    }

    std::string Card::ToString() const
    {
        return "r: " + _rank + " c: " + _colour;
    }
}
