#include "interface/UiLogicDispatcher.hpp"

#include "entities/decks/CardDeck.hpp"
#include "gamemanagers/CreateGameManager.hpp"

#include <any>
#include <memory>
#include <stdexcept>

namespace cardmultigame::interface
{
    namespace
    {
        // The exhaustive std::any -> string dispatch validated by the Slice-2 PoC (task doc 06).
        // The bag only ever holds shared_ptr<CardDeck>, int, bool. Throw on anything else — never a
        // silent "" fallback, so a forgotten branch fails loud (DA #1/#2/#6).
        std::string DisplayValue(const std::any& value)
        {
            if (value.type() == typeid(std::shared_ptr<entities::decks::CardDeck>))
            {
                return std::any_cast<std::shared_ptr<entities::decks::CardDeck>>(value)->ToString();
            }
            if (value.type() == typeid(int))
            {
                return std::to_string(std::any_cast<int>(value));
            }
            if (value.type() == typeid(bool))
            {
                return std::any_cast<bool>(value) ? "True" : "False"; // C++ bool prints 0/1 — force True/False
            }
            throw std::runtime_error("Unknown value type in GameState display");
        }
    }

    UiLogicDispatcher::UiLogicDispatcher()
        : _gameManager(gamemanagers::CreateGameManager().Empty())
    {
    }

    void UiLogicDispatcher::DoStuff(const std::string& orders)
    {
        _gameManager.ExecuteOrders(orders);
    }

    void UiLogicDispatcher::SetupGame(const std::string& orders)
    {
        _gameManager = gamemanagers::CreateGameManager().DefaultsWithOrders(orders);
    }

    std::string UiLogicDispatcher::DisplayCurrentState()
    {
        // Mirrors C# string.Join(";"+NewLine, currentState): "[key, value]" per entry, insertion order.
        std::string result;
        bool first = true;
        for (const auto& [key, value] : _gameManager.CurrentState().Entries())
        {
            if (!first) result += ";\n";
            result += "[" + key + ", " + DisplayValue(value) + "]";
            first = false;
        }
        return result;
    }
}
