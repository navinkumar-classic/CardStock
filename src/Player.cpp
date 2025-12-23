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

void Player::addZone(const std::string& zoneName, CardZone* zone) {
    zones[zoneName] = zone;
}

CardZone* Player::getZone(const std::string& zoneName) const {
    auto it = zones.find(zoneName);
    if (it != zones.end())
        return it->second;
    return nullptr;
}

const Player::ZoneMap& Player::getAllZones() const {
    return zones;
}

size_t Player::getZoneSize(const std::string& zoneName) const {
    auto it = zones.find(zoneName);
    if (it != zones.end())
        return it->second->size();
    return 0;
}

bool Player::addCardToZoneTop(const std::string& zoneName, Card&& card) const {
    CardZone* zone = getZone(zoneName);
    if (!zone)
        return false;

    zone->pushFront(std::move(card));
    return true;
}

bool Player::addCardToZoneBottom(const std::string& zoneName, Card&& card) const {
    CardZone* zone = getZone(zoneName);
    if (!zone)
        return false;

    zone->pushBack(std::move(card));
    return true;
}
