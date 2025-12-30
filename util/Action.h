
#pragma once

#include "../include/Player.h"
#include "../include/PlayerList.h"

namespace Action {

    void drawCardFromDeck(Player& player, CardZoneMap& cardZoneMap, const std::string& handName, const std::string& deckName, int numCards);
    void playCard(Player& player, CardZoneMap& cardZoneMap, const std::string& handName, const std::string& deckName, int cardIndex);
    void goToStartPhase(PlayerList& playerList);

    template <varTypeName T> void setPlayerState(Player& player, const std::string& stateName, T value) {
        player.state.set<T>(stateName, value);
    }

    Player& getCurrentPlayer(PlayerList& playerList);

}
