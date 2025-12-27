
#pragma once

#include <functional>
#include <map>
#include <string>

using eventFunction = std::function<bool()>;
using effectFunction = std::function<bool()>;

class EventManager {
public:
    EventManager() = default;
    ~EventManager() = default;

    bool addEvent(const std::string& name, eventFunction event, effectFunction effect);
    bool removeEvent(const std::string& name);

    bool run();

private:
    using eventPair = std::pair<eventFunction, effectFunction>;
    std::map<std::string, eventPair> eventMap;
};