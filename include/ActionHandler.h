
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
