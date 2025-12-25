//
// Created by echel on 24/12/2025.
//

#pragma once

#include <string>
#include <unordered_map>
#include "nlohmann/json.hpp"

#include "CardZone.h"
#include "Card.h"

class CardZoneMap {
public:
    using ZoneMap = std::unordered_map<std::string, CardZone>;
    using json = nlohmann::json;

    bool addZone(const std::string& name, CardZone&& zone);
    CardZone* getZone(const std::string& name);
    const CardZone* getZone(const std::string& name) const;

    bool hasZone(const std::string& name) const;
    size_t getZoneSize(const std::string& name) const;

    const ZoneMap& getAllZones() const;

    bool addCardTop(const std::string& zoneName, Card&& card);
    bool addCardBottom(const std::string& zoneName, Card&& card);

    void initFromJson(const json& j);
    json toJson() const;

private:
    ZoneMap zones;
};
