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

#include "Card.h"
#include "CardZoneMap.h"

class Player {
    public:
        Player(int id, const std::string &name);
        Player(const json& j);

        int getId() const;

        const std::string &getName() const;

        CardZoneMap zoneMap;
        GameState state;

        void initFromJson(const json& j);
        json toJson() const;

    private:
        int playerId{};
        std::string name;
};
