#include "gamemanagers/selectedrules/creationcommands/SetDeck.hpp"

#include "entities/decks/CreateCardDeck.hpp"
#include "technical/StringUtils.hpp"

namespace cardmultigame::gamemanagers::selectedrules::creationcommands
{
    void SetDeck::ChangeGameRuleset(GameManagerInternalsBuilder& builder, const std::string& parameters)
    {
        std::shared_ptr<entities::decks::CardDeck> deck = entities::decks::CreateCardDeck().FromGivenCards(parameters);
        builder.SetDeck(deck);
    }

    bool SetDeck::ShouldReactTo(const std::string& outerCommandName)
    {
        return technical::ToLower(_identifier) == technical::ToLower(outerCommandName);
    }
}
