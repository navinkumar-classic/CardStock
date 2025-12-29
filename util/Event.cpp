
#include "Event.h"

bool Event::hasEmptyCardZone(const Player &player, const std::string &zoneName) {
    return player.zoneMap.getZone(zoneName)->empty();
}

bool Event::anyPlayerHasEmptyDeck(const PlayerList &players, const std::string &zoneName) {
    for (const auto &player : players) {
        if (hasEmptyCardZone(player, zoneName))
            return true;
    }
    return false;
}

bool Event::allPlayersHaveEmptyDeck(const PlayerList &players, const std::string &zoneName) {
    for (const auto &player : players) {
        if (!hasEmptyCardZone(player, zoneName))
            return false;
    }
    return true;
}

void Event::gameOver(GameState& gameState) {
    gameState.set<bool>("isRunning", false);
}