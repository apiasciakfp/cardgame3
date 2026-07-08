#include "gamemanagers/selectedrules/creationcommands/GameVariant.hpp"

#include "technical/StringUtils.hpp"
#include "usecases/cardcomparison/BlackRedColourOnlyComparisonStrategy.hpp"

#include <memory>

namespace cardmultigame::gamemanagers::selectedrules::creationcommands
{
    void GameVariant::ChangeGameRuleset(GameManagerInternalsBuilder& builder, const std::string& parameters)
    {
        // The parameter is IGNORED — always sets BlackRed (WART-11). `GameVariant RedBlack` and
        // `GameVariant anything` are identical.
        (void)parameters;
        builder.SetCardComparisonStrategy(std::make_shared<usecases::cardcomparison::BlackRedColourOnlyComparisonStrategy>());
    }

    bool GameVariant::ShouldReactTo(const std::string& outerCommandName)
    {
        return technical::ToLower(_identifier) == technical::ToLower(outerCommandName);
    }
}
