
#include "../include/PlayerList.h"

void PlayerList::applyToAllPlayers(const applyFunc& func, CardZoneMap& cardZoneMap, GameState& gameState) {
    for (auto& player: players) {
        func(player, cardZoneMap, gameState);
    }
}

void PlayerList::applyToPlayers(const std::vector<size_t>& indList, const applyFunc& func, CardZoneMap& cardZoneMap, GameState& gameState) {

    for (auto ind : indList) {
        if (ind < players.size()) {
            func(players.at(ind), cardZoneMap, gameState);
        }
    }
}

void PlayerList::applyToAllPlayersExcept(const std::vector<size_t> &indList, const applyFunc& func, CardZoneMap& cardZoneMap, GameState& gameState) {
    for (size_t i = 0; i < players.size(); ++i) {
        bool notInList = true;

        for (size_t idx : indList) {
            if (i == idx) {
                notInList = false;
                break;
            }
        }

        if (notInList) {
            func(players.at(i), cardZoneMap, gameState);
        }
    }
}

void PlayerList::applyTransfer(size_t srcInd, size_t tarInd, const transferFunc& func, GameState& gameState) {
    if (srcInd < players.size() && tarInd < players.size()) {
        func(players.at(srcInd), players.at(tarInd), gameState);
    }
}

void PlayerList::initFromJson(const json& playersConfig) {
    for (auto j: playersConfig) {
        if (j.is_object()) {
            if (j.contains("id") && j.contains("name") && j["id"].is_number_integer() && j["name"].is_string()) {
                players.emplace_back(j);
            }
        }
    }
}

json PlayerList::toJson() const {
    json j = json::array();

    for (auto& player: players) {
        j.push_back(player.toJson());
    }

    return j;
}
