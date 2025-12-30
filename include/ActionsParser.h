#pragma once
#include <functional>

#include "ActionHandler.h"
#include "EventManager.h"
#include "PlayerList.h"

using conditionRegister = std::function<std::pair<bool, std::vector<int>>(Player&, CardZoneMap&, GameState&, const json&)>;
using actionRegister = std::function<bool(PlayerList&, CardZoneMap&, GameState&, int cardId, const json&)>;

class ActionsParser {
    public:
        ActionsParser() = default;
        ~ActionsParser() = default;

        void init();
        void parseAction(ActionHandler& actionHandler, const json& eventJson);

    private:
        std::map<std::string, conditionRegister> conditionRegisterMap;
        std::map<std::string, actionRegister> actionRegisterMap;

};