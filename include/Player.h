/**
* @file Player.h
 * @brief represents the player entity
 *
 * Header file containing the player entity
 *
 * @author Navin Kumar<omnavinyogesh.icc@gmail.com>
 * @date 2025-12-22
 * @version 0.1.0
 * @copyright
 *
 * Change Log:
 * - 2025-12-22: file created ~ Navin Kumar.
 */

#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "Card.h"
#include "CardZone.h"
#include "CardZoneMap.h"

class Player {
public:
 Player(int id, const std::string& name);

 int getId() const;
 const std::string& getName() const;

 bool addZone(const std::string& zoneName, CardZone &&zone);
 CardZone* getZone(const std::string &zoneName);
 const CardZone* getZone(const std::string& zoneName) const;
 const CardZoneMap::ZoneMap& getAllZones() const;
 size_t getZoneSize(const std::string& zoneName) const;

 bool addCardToZoneTop(const std::string &zoneName, Card &&card);
 bool addCardToZoneBottom(const std::string &zoneName, Card &&card);

private:
 int playerId;
 std::string name;

 CardZoneMap zoneMap;
 GameState state;
};
