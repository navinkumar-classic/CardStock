
#pragma once
#include "../include/Player.h"
#include "../include/PlayerList.h"

namespace Event {

    bool hasEmptyCardZone(const Player& player, const std::string& zoneName);
    bool anyPlayerHasEmptyDeck(const PlayerList& players, const std::string& zoneName);
    bool allPlayersHaveEmptyDeck(const PlayerList& players, const std::string& zoneName);

}
