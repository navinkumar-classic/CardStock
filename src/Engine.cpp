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
}

void Engine::run() {
    onInit();
    while (getIsRunning()) {
        update();
    }
    onExit();
}

void Engine::onInit() {
    std::cout << "Engine Initialized!" << std::endl;
}

void Engine::update() {
    std::cout << "Engine Updated!" << std::endl;
}

void Engine::onExit() {
    std::cout << "Engine Exiting!" << std::endl;
}

void Engine::applyToAllPlayers(const applyFunc& func) {
    for (auto& player: players) {
        func(player, cardZoneMap, gameState);
    }
}

void Engine::applyToPlayers(const std::vector<size_t>& indList, const applyFunc& func) {

    for (auto ind : indList) {
        if (ind < players.size()) {
            func(players.at(ind), cardZoneMap, gameState);
        }
    }
}

void Engine::applyToAllPlayersExcept(const std::vector<size_t> &indList, const applyFunc& func) {
    for (size_t i = 0; i < players.size(); ++i) {
        bool notInList = true;

        for (size_t idx : indList) {
            if (i == idx) {
                notInList = false;
                break;
            }
        }

        if (notInList) {
            func(players.at(i), cardZoneMap, gameState);
        }
    }
}

void Engine::applyTransfer(size_t srcInd, size_t tarInd, const transferFunc& func) {
    if (srcInd < players.size() && tarInd < players.size()) {
        func(players.at(srcInd), players.at(tarInd), gameState);
    }
}



void Engine::addPlayers(size_t numPlayers, const std::vector<json>& playersConfig) {

    for (auto j: playersConfig) {
        if (j.is_object()) {
            if (j.contains("id") && j.contains("name") && j["id"].is_number_integer() && j["name"].is_string()) {
                players.emplace_back(j);
            }
        }
    }

    if (numPlayers == players.size()) {
        return;
    }
    throw std::invalid_argument("Invalid json provided");
}
