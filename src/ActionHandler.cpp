/**
* @file ActionHandler.cpp
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
 * - 2025-12-23: implemented actionConditionMap, actionPair and ability to add, remove and execute actions ~ Navin Kumar.
 */

#include "../include/ActionHandler.h"

bool ActionHandler::addAction(const std::string &name, conditionFunction condition, actionFunction action) {
    if (actionConditionMap.contains(name)) {
        return false;
    }

    actionConditionMap[name] = actionPair {std::move(condition), std::move(action)};
    return true;
}

bool ActionHandler::removeAction(const std::string &name) {
    return actionConditionMap.erase(name);
}

validActions ActionHandler::getValidAction(Player& player, CardZoneMap& cardZoneMap, GameState& gameState) {
    validActions res;

    for (const auto& [name, action] : actionConditionMap) {
        auto condition = action.first(player, cardZoneMap, gameState);
        if (condition.first) {
            res.emplace_back(name, condition.second);
        }
    }

    return res;
}

bool ActionHandler::execute(const std::string &action, PlayerList& playerList, CardZoneMap& cardZoneMap, GameState& gameState, int cardId) const {
    if (actionConditionMap.contains(action)) {
        return actionConditionMap.at(action).second(playerList, cardZoneMap, gameState, cardId);
    }
    return false;
}
