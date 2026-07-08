#include "entities/gamestates/GameState.hpp"

namespace cardmultigame::entities::gamestates
{
    std::any GameState::Get(std::string_view key) const
    {
        const auto at = _values.find(std::string(key));
        if (at == _values.end())
        {
            return std::any{}; // empty any == the C# null on a missing key (WART-5)
        }
        return at->second;
    }

    void GameState::Set(std::string_view key, std::any value)
    {
        const std::string keyString(key);
        if (_values.find(keyString) == _values.end())
        {
            _order.push_back(keyString);
        }
        _values[keyString] = std::move(value);
    }

    bool GameState::ContainsKey(std::string_view key) const
    {
        return _values.find(std::string(key)) != _values.end();
    }

    std::vector<std::pair<std::string, std::any>> GameState::Entries() const
    {
        std::vector<std::pair<std::string, std::any>> entries;
        entries.reserve(_order.size());
        for (const auto& key : _order)
        {
            entries.emplace_back(key, _values.at(key));
        }
        return entries;
    }
}
