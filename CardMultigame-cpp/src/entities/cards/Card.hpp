#pragma once

#include <string>

namespace cardmultigame::entities::cards
{
    // Plain class, NO operator== — reference (identity) equality, exactly as the C# original.
    // Held by std::shared_ptr; CardDeck erases the drawn card by pointer identity.
    class Card
    {
        std::string _rank;
        std::string _colour;

    public:
        Card(std::string rank, std::string colour);

        std::string Rank() const;
        std::string Colour() const;

        std::string ToString() const;
    };
}
