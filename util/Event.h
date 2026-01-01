
#pragma once
#include "../include/Player.h"
#include "../include/PlayerList.h"

namespace Event {

    bool hasEmptyCardZone(const Player& player, const std::string& zoneName);
    bool hasLessThanNCards(const Player&, const std::string& zoneName, size_t n);
    bool hasMoreThanNCards(const Player&, const std::string& zoneName, size_t n);

    bool anyPlayerHasEmptyDeck(const PlayerList& players, const std::string& zoneName);
    bool allPlayersHaveEmptyDeck(const PlayerList& players, const std::string& zoneName);
    bool anyPlayerHasDeckBelow(const PlayerList&, const std::string& zoneName, size_t n);
    bool allPlayersHaveDeckBelow(const PlayerList&, const std::string& zoneName, size_t n);
    bool anyPlayerHasDeckAbove(const PlayerList&, const std::string& zoneName, size_t n);
    bool allPlayersHaveDeckAbove(const PlayerList&, const std::string& zoneName, size_t n);

    bool andEvents(const std::vector<bool>& events);
    bool orEvents(const std::vector<bool>& events);
    bool notEvent(bool event);
    bool xorEvents(const std::vector<bool>& events);

}
