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

int Player::getId() const {
    return playerId;
}

const std::string& Player::getName() const {
    return name;
}
