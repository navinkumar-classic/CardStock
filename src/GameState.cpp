/**
* @file GameState.cpp
 * @brief represents the game state entity
 *
 * Header file containing the game state entity
 *
 * @author Navin Kumar<omnavinyogesh.icc@gmail.com>
 * @date 2025-12-22
 * @version 0.1.0
 * @copyright
 *
 * Change Log:
 * - 2025-12-24: created file ~ Navin Kumar.
 * - 2025-12-24: implementated functionality to serialize/deserialize into JSON ~ Navin Kumar.
 */

#include "../include/GameState.h"

void GameState::initFromJson(const json& j) {
    for (auto& [key, value] : j.items()) {
        if (value.is_number_integer())
            set(key, value.get<int>());
        else if (value.is_number_float())
            set(key, value.get<float>());
        else if (value.is_boolean())
            set(key, value.get<bool>());
        else if (value.is_string())
            set(key, value.get<std::string>());
    }
}

json GameState::toJson() const {
    json j = json::object();

    for (auto &[fst, snd] : gameStateMap) {
        std::visit([&](const auto& v){ j[fst] = v; }, snd);
    }

    return j;
}
