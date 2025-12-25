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
        throw std::invalid_argument("Invalid json provided");
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

void Engine::addPlayers(size_t numPlayers, const std::vector<json>& playersConfig) {

    for (auto j: playersConfig) {
        if (j.is_object()) {
            if (j.contains("id") && j.contains("name") && j["id"].is_number_integer() && j["name"].is_string()) {
                players.emplace_back(j["id"], j["name"]);
            }
        }
    }

    if (numPlayers == players.size()) {
        return;
    }
    throw std::invalid_argument("Invalid json provided");
}
