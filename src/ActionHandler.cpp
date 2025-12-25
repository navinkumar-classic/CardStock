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

bool ActionHandler::addAction(const std::string &name, std::function<bool()> condition, std::function<bool()> action) {
    if (actionConditionMap.contains(name)) {
        return false;
    }

    actionConditionMap[name] = actionPair {std::move(condition), std::move(action)};
    return true;
}

bool ActionHandler::removeAction(const std::string &name) {
    return actionConditionMap.erase(name);
}

std::vector<std::string> ActionHandler::getValidAction() {
    std::vector<std::string> res;

    for (const auto& [name, action] : actionConditionMap) {
        if (action.first()) {
            res.emplace_back(name);
        }
    }

    return res;
}

bool ActionHandler::execute(const std::string &action) const {
    if (actionConditionMap.contains(action)) {
        return actionConditionMap.at(action).second();
    }
    return false;
}
