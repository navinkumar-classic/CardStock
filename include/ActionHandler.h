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

class ActionHandler {
    public:
        ActionHandler() = default;
        ~ActionHandler() = default;

        bool addAction(const std::string& name, std::function<bool()> condition, std::function<bool()> action);
        bool removeAction(const std::string& name);

        std::vector<std::string> getValidAction();

        [[nodiscard]] bool execute(const std::string& action) const;

    private:
        using actionPair = std::pair<std::function<bool()>, std::function<bool()>>;
        std::map<std::string, actionPair> actionConditionMap;
};
