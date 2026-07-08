#pragma once

#include "gamemanagers/GameManager.hpp"

#include <string>

namespace cardmultigame::interface
{
    class UiLogicDispatcher
    {
        gamemanagers::GameManager _gameManager;

    public:
        UiLogicDispatcher();

        void DoStuff(const std::string& orders);
        void SetupGame(const std::string& orders);
        std::string DisplayCurrentState();
    };
}
