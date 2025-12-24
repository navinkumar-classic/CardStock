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

bool Player::addZone(const std::string& zoneName, CardZone &&zone) {
    return zoneMap.addZone(name, std::move(zone));
}

CardZone* Player::getZone(const std::string& zoneName) {
    return zoneMap.getZone(zoneName);
}

const CardZone* Player::getZone(const std::string& zoneName) const {
    return zoneMap.getZone(zoneName);
}

const CardZoneMap::ZoneMap& Player::getAllZones() const {
    return zoneMap.getAllZones();
}

size_t Player::getZoneSize(const std::string& zoneName) const {
    return zoneMap.getZoneSize(zoneName);
}

bool Player::addCardToZoneTop(const std::string& zoneName, Card&& card) {
    return zoneMap.addCardTop(zoneName, std::move(card));
}

bool Player::addCardToZoneBottom(const std::string& zoneName, Card&& card) {
    return zoneMap.addCardBottom(zoneName, std::move(card));
}
