/**
* @file Player.cpp
 * @brief represents the player entity
 *
 * Implementation of the player entity
 *
 * @author Vishal R<echelora@gmail.com>
 * @date 2025-12-24
 * @version 0.1.0
 * @copyright
 *
 * Change Log:
 * - 2025-12-24: file created ~ Vishal
 */

#include "../include/Player.h"

Player::Player(int id, const std::string& name)
    : playerId(id), name(name) {}

Player::Player(const json &j): playerId(-1), name("null")  {
    initFromJson(j);
}

int Player::getId() const {
    return playerId;
}

const std::string& Player::getName() const {
    return name;
}

void Player::initFromJson(const json& j) {
    if (j.contains("id") && j["id"].is_number_integer()) {
        playerId = j["id"];
    }
    if (j.contains("name") && j["name"].is_string()) {
        name = j["name"];
    }
    if (j.contains("state") && j.is_object()) {
        state.initFromJson(j["state"]);
    }
    if (j.contains("cardZoneMap") && j["cardZoneMap"].is_object()) {
        zoneMap.initFromJson(j["cardZoneMap"]);
    }
}

json Player::toJson() const {
    json j = json::object();

    j["id"] = playerId;
    j["name"] = name;
    j["state"] = state.toJson();
    j["cardZoneMap"] = zoneMap.toJson();

    return j;
}
