/**
* @file ActionHandler.h
 * @brief represents the action handler entity
 *
 * Implementing an action handler entity
 *
 * @author Navin Kumar<omnavinyogesh.icc@gmail.com>
 * @date 2025-12-22
 * @version 0.1.0
 * @copyright
 *
 * Change Log:
 * - 2025-12-25: file created ~ Navin Kumar.
 * - 2025-12-23: added actionConditionMap, actionPair and ability to add, remove and execute actions ~ Navin Kumar.
 */
#pragma once
#include <functional>
#include <map>
#include <string>

#include "Player.h"
#include "PlayerList.h"

using conditionFunction = std::function<std::pair<bool, std::vector<int>>(Player&, CardZoneMap&, GameState&)>;
using actionFunction = std::function<bool(PlayerList&, CardZoneMap&, GameState&, int cardId)>;
using validActions = std::vector<std::pair<std::string, std::vector<int>>>;

class ActionHandler {
    public:
        ActionHandler() = default;
        ~ActionHandler() = default;

        bool addAction(const std::string& name, conditionFunction condition, actionFunction action);
        bool removeAction(const std::string& name);

        validActions getValidAction(Player& player, CardZoneMap& cardZoneMap, GameState& gameState);

        bool execute(const std::string& action, PlayerList& playerList, CardZoneMap& cardZoneMap, GameState& gameState, int cardId) const;

    private:
        using actionPair = std::pair<conditionFunction, actionFunction>;
        std::map<std::string, actionPair> actionConditionMap;
};
