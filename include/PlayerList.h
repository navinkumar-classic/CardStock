

#pragma once
#include <vector>
#include "Player.h"
#include "TurnManager.h"

using applyFunc = std::function<void(Player&, CardZoneMap&, GameState&)>;
using transferFunc = std::function<void(Player&, Player&, GameState&)>;

class PlayerList {
    public:
        PlayerList();
        PlayerList(const json& json);

        auto begin() { return players.begin(); }
        auto end() { return players.end(); }
        auto& at(size_t index) { return players.at(index); }
        [[nodiscard]] auto size() const { return players.size(); }

        void applyToAllPlayers(const applyFunc& func, CardZoneMap& cardZoneMap, GameState& gameState);
        void applyToPlayers(const std::vector<size_t>& indList, const applyFunc& func, CardZoneMap& cardZoneMap, GameState& gameState);
        void applyToAllPlayersExcept(const std::vector<size_t> &indList, const applyFunc& func, CardZoneMap& cardZoneMap, GameState& gameState);
        void applyTransfer(size_t srcInd, size_t tarInd, const transferFunc& func, GameState& gameState);

        void initFromJson(const json& json);
        [[nodiscard]] json toJson() const;

        TurnManager turnManager;

    private:
        std::vector<Player> players;
};
