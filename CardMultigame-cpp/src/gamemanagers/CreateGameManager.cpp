#include "gamemanagers/CreateGameManager.hpp"

#include "entities/gamestates/CreateGameState.hpp"
#include "gamemanagers/GameManagerInternalsBuilder.hpp"
#include "gamemanagers/selectedrules/CreateGameStructure.hpp"
#include "gamemanagers/selectedrules/CreatePlayedGameRules.hpp"
#include "technical/parsers/SelectedParser.hpp"

#include <utility>

namespace cardmultigame::gamemanagers
{
    GameManager CreateGameManager::DefaultsWithOrders(const std::string& orderString)
    {
        const std::vector<std::pair<std::string, std::string>> orders = technical::parsers::SelectedParser().ProperlyParse(orderString);

        GameManagerInternalsBuilder builder = selectedrules::CreateGameStructure().BuildRulesAndInitialState(orders);

        std::shared_ptr<selectedrules::PlayedGameRules> rules = builder.ConstructRuleset();
        entities::gamestates::GameState initialState = builder.ConstructGameState();

        return GameManager(std::move(initialState), rules);
    }

    GameManager CreateGameManager::Empty()
    {
        entities::gamestates::GameState initialState = entities::gamestates::CreateGameState().Default();
        std::shared_ptr<selectedrules::PlayedGameRules> rules = selectedrules::CreatePlayedGameRules().Empty();

        return GameManager(std::move(initialState), rules);
    }
}
