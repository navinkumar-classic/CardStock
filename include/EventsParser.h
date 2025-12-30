
#pragma once
#include <functional>

#include "ActionHandler.h"
#include "EventManager.h"
#include "PlayerList.h"

using EventRegister = std::function<bool(PlayerList&, CardZoneMap&, GameState&, const json&)>;
using EffectRegister = std::function<bool(PlayerList&, CardZoneMap&, GameState&, const json&)>;

class EventsParser {
    public:
        EventsParser() = default;
        ~EventsParser() = default;

        void init();
        void parseEvent(EventManager& eventManager, const json& eventJson);

    private:
        void initEvent();
        void initEffect();

        std::map<std::string, EventRegister> eventRegisterMap;
        std::map<std::string, EffectRegister> effectRegisterMap;
};