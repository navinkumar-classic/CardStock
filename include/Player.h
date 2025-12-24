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

class Player {
public:
 using ZoneMap = std::unordered_map<std::string, CardZone>;

 Player(int id, const std::string& name);

 int getId() const;
 const std::string& getName() const;

 void addZone(const std::string& zoneName, CardZone &&zone);

 CardZone *getZone(const std::string &zoneName);
 const CardZone* getZone(const std::string& zoneName) const;
 const ZoneMap& getAllZones() const;
 size_t getZoneSize(const std::string& zoneName) const;

 bool addCardToZoneTop(const std::string &zoneName, Card &&card) const;
 bool addCardToZoneBottom(const std::string &zoneName, Card &&card) const;

private:
 int playerId;
 std::string name;

 ZoneMap zones;
 GameState state;
};