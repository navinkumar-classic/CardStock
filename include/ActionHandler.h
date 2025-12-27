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

using conditionFunction = std::function<bool()>;
using actionFunction = std::function<bool()>;

class ActionHandler {
    public:
        ActionHandler() = default;
        ~ActionHandler() = default;

        bool addAction(const std::string& name, conditionFunction condition, actionFunction action);
        bool removeAction(const std::string& name);

        std::vector<std::string> getValidAction();

        [[nodiscard]] bool execute(const std::string& action) const;

    private:
        using actionPair = std::pair<conditionFunction, actionFunction>;
        std::map<std::string, actionPair> actionConditionMap;
};
