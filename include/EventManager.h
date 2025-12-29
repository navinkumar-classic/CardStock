
#pragma once

#include <functional>
#include <map>
#include <string>

#include "CardZoneMap.h"
#include "GameState.h"
#include "PlayerList.h"

using eventFunction = std::function<bool(PlayerList&, CardZoneMap&, GameState&)>;
using effectFunction = std::function<bool(PlayerList&, CardZoneMap&, GameState&)>;

class EventManager {
public:
    EventManager() = default;
    ~EventManager() = default;

    bool addEvent(const std::string& name, eventFunction event, effectFunction effect);
    bool removeEvent(const std::string& name);

    bool run(PlayerList& players, CardZoneMap& cardZoneMap, GameState& gameState);

private:
    using eventPair = std::pair<eventFunction, effectFunction>;
    std::map<std::string, eventPair> eventMap;
};