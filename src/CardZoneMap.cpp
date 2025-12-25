//
// Created by echel on 24/12/2025.
//

#include "../include/CardZoneMap.h"


bool CardZoneMap::addZone(const std::string& name, CardZone&& zone) {
    return zones.emplace(name, std::move(zone)).second;
}

CardZone* CardZoneMap::getZone(const std::string& name) {
    auto it = zones.find(name);
    return (it != zones.end()) ? &it->second : nullptr;
}

const CardZone* CardZoneMap::getZone(const std::string& name) const {
    auto it = zones.find(name);
    return (it != zones.end()) ? &it->second : nullptr;
}

bool CardZoneMap::hasZone(const std::string& name) const {
    return zones.contains(name);
}

size_t CardZoneMap::getZoneSize(const std::string& name) const {
    auto it = zones.find(name);
    return (it != zones.end()) ? it->second.size() : 0;
}

const CardZoneMap::ZoneMap& CardZoneMap::getAllZones() const {
    return zones;
}

bool CardZoneMap::addCardTop(const std::string& zoneName, Card&& card) {
    CardZone* zone = getZone(zoneName);
    if (!zone)
        return false;

    zone->pushFront(std::move(card));
    return true;
}

bool CardZoneMap::addCardBottom(const std::string& zoneName, Card&& card) {
    CardZone* zone = getZone(zoneName);
    if (!zone)
        return false;

    zone->pushBack(std::move(card));
    return true;
}

void CardZoneMap::initFromJson(const json& j) {
    zones.clear();

    for (auto it = j.begin(); it != j.end(); ++it) {
        const std::string& zoneName = it.key();
        const json& zoneJson = it.value();

        CardZone zone(false); //hidden will be set by init
        zone.initFromJson(zoneJson);

        zones.emplace(zoneName, std::move(zone));
    }
}

CardZoneMap::json CardZoneMap::toJson() const {
    json j = json::object();

    for (const auto& [zoneName, zone] : zones) {
        j[zoneName] = zone.toJson();
    }
    return j;
}
