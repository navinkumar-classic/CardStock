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
#include "Player.h"

class Engine {
    public:
        Engine(const json& config);
        ~Engine() = default;

        void run();

        [[nodiscard]] bool getIsRunning() const { return isRunning; }
        void setIsRunning(bool value) { isRunning = value; }

        auto playersBegin() { return players.begin(); }
        auto playersEnd() { return players.end(); }
        auto& playersAt(size_t index) { return players.at(index); }
        auto playersSize() const { return players.size(); }

        ActionHandler actionHandler;
        CardZoneMap cardZoneMap;

    private:
        void onInit();
        void update();
        void onExit();

        void addPlayers(size_t numPlayers, const std::vector<json>& playersConfig);

        bool isRunning = true;

        std::vector<Player> players;
};
