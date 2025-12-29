/**
* @file Engine.h
 * @brief represents an engine for a turn-based card game
 *
 * Header file containing an engine for a turn-based card game
 *
 * @author Navin Kumar<omnavinyogesh.icc@gmail.com>
 * @date 2025-12-22
 * @version 0.1.0
 * @copyright
 *
 * Change Log:
 * - 2025-12-22: file created ~ Navin Kumar.
 * - 2025-12-25: added basic life cycle functions ~ Navin Kumar.
 */

#pragma once
#include "ActionHandler.h"
#include "Card.h"
#include "EventManager.h"
#include "PlayerList.h"

using initExitFunction = std::function<void(PlayerList&, CardZoneMap&, GameState&)>;

class Engine {
    public:
        Engine(const json& config);
        ~Engine() = default;

        void run();

        PlayerList players;
        ActionHandler actionHandler;
        CardZoneMap cardZoneMap;
        GameState gameState;
        EventManager eventManager;

    private:
        void onInit();
        void update();
        void onExit();

        void addPlayers(size_t numPlayers, const json &playersConfig);

        std::vector<initExitFunction> initFunctions;
        std::vector<initExitFunction> exitFunctions;

        validActions tempValidActions = {};
        json tempValidActionsJson = {};
        std::pair<std::string, int> tempActionExecute = {};
};
