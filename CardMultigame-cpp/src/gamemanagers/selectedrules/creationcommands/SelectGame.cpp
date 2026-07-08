#include "gamemanagers/selectedrules/creationcommands/SelectGame.hpp"

#include "entities/games/IGameImplementation.hpp"
#include "entities/games/guessing/GuessACardGame.hpp"
#include "technical/StringUtils.hpp"

#include <memory>
#include <stdexcept>

namespace cardmultigame::gamemanagers::selectedrules::creationcommands
{
    namespace
    {
        std::shared_ptr<entities::games::IGameImplementation> SelectGameImplementation(const std::string& parameters)
        {
            std::shared_ptr<entities::games::IGameImplementation> gameImpl = nullptr;
            if (technical::ToLower(parameters) == technical::ToLower("GuessACard"))
            {
                gameImpl = std::make_shared<entities::games::guessing::GuessACardGame>();
            }

            if (gameImpl == nullptr)
            {
                throw std::invalid_argument("Either the game is not registered in factory or game identifier has a typo. Got: " + parameters);
            }

            return gameImpl;
        }
    }

    void SelectGame::ChangeGameRuleset(GameManagerInternalsBuilder& builder, const std::string& parameters)
    {
        std::shared_ptr<entities::games::IGameImplementation> gameImpl = SelectGameImplementation(parameters);

        builder.SetName(gameImpl->Title());
        builder.SetDeck(gameImpl->CardDeck());
        builder.SetAvailableActions(gameImpl->AvailableActions());
        builder.SetVictoryConditions(gameImpl->VictoryConditions());
        builder.SetGameStopConditions(gameImpl->GameStopConditions());
        builder.SetInitialGameState(gameImpl->InitialGameState());
        builder.SetCardComparisonStrategy(gameImpl->CardComparisonStrategy());
    }

    bool SelectGame::ShouldReactTo(const std::string& outerCommandName)
    {
        return technical::ToLower(_identifier) == technical::ToLower(outerCommandName);
    }
}
