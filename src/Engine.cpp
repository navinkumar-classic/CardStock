/**
* @file Engine.cpp
 * @brief represents an engine for a turn-based card game
 *
 * implementation of an engine for a turn-based card game
 *
 * @author Navin Kumar<omnavinyogesh.icc@gmail.com>
 * @date 2025-12-22
 * @version 0.1.0
 * @copyright
 *
 * Change Log:
 * - 2025-12-22: file created ~ Navin Kumar.
 * - 2025-12-25: implemented basic life cycle functions ~ Navin Kumar.
 */

#include "../include/Engine.h"
#include <iostream>

Engine::Engine(const json& config) {
    if (config.contains("players") && config["players"].is_array() && config.contains("numPlayers") && config["numPlayers"].is_number_integer()) {
        addPlayers(config["numPlayers"], config["players"]);
    }
    else {
        throw std::invalid_argument("Invalid json provided - players information missing");
    }

    if (config.contains("gameState") && config["gameState"].is_object()) {
        gameState.initFromJson(config["gameState"]);
    }

    if (config.contains("cardZoneMap") && config["cardZoneMap"].is_object()) {
        cardZoneMap.initFromJson(config["cardZoneMap"]);
    }

    turnManager.init(players.size());
}

void Engine::run() {
    onInit();
    while (getIsRunning()) {
        update();
    }
    onExit();
}

void Engine::onInit() {
    for (auto& initFunction: initFunctions) {
        initFunction(players, cardZoneMap, gameState);
    }
}

void Engine::update() {
    switch (turnManager.getPhase()) {
        case TurnPhase::Start:
            std::cout << "Turn Phase: Start" << std::endl;
            turnManager.nextPhase();
            break;

        case TurnPhase::Main:
            std::cout << "Turn Phase: Main" << std::endl;
            turnManager.nextPhase();
            break;

        case TurnPhase::End:
            std::cout << "Turn Phase: End" << std::endl;
            turnManager.endTurn();
            break;
    }
}

void Engine::onExit() {
    for (auto& exitFunction: initFunctions) {
        exitFunction(players, cardZoneMap, gameState);
    }
}

void Engine::addPlayers(size_t numPlayers, const json& playersConfig) {
    players.initFromJson(playersConfig);

    if (numPlayers == players.size()) {
        return;
    }
    throw std::invalid_argument("Invalid json provided");
}
