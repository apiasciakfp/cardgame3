#pragma once

// The EncapsulatedContext bag. Mirrors C# `GameState : Dictionary<string, object>` whose custom
// indexer returns null on a missing key (WART-5). Faithful C++: an INSERTION-ORDERED map of
// string -> std::any, where a missing key yields an EMPTY std::any (the "null"). std::any is the
// analog of C# `object` boxing; the bag only ever holds shared_ptr<CardDeck>, int, and bool.
// (Header depends only on <any> — no CardDeck include; any_cast sites include CardDeck themselves.)

#include <any>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

namespace cardmultigame::entities::gamestates
{
    class GameState
    {
        std::vector<std::string> _order;                  // insertion order (drives display order)
        std::unordered_map<std::string, std::any> _values;

    public:
        // Missing key -> empty std::any (no throw), reproducing the C# indexer's null (WART-5).
        std::any Get(std::string_view key) const;

        // Insert-or-assign; a new key is appended to the order, an existing key keeps its slot.
        void Set(std::string_view key, std::any value);

        bool ContainsKey(std::string_view key) const;

        // Key/value pairs in insertion order (for iteration + display).
        std::vector<std::pair<std::string, std::any>> Entries() const;
    };
}
