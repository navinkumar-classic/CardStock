

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
