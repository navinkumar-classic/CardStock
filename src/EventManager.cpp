
#include "../include/EventManager.h"

bool EventManager::addEvent(const std::string &name, eventFunction event, effectFunction effect) {
    if (eventMap.contains(name)) {
        return false;
    }

    eventMap[name] = eventPair {std::move(event), std::move(effect)};
    return true;
}

bool EventManager::removeEvent(const std::string &name) {
    return eventMap.erase(name);
}

bool EventManager::run() {
    bool res = false;

    for (const auto& [name, event] : eventMap) {

        if (event.first()) {
            res = event.second();
        }
        if (!res) return false;
    }

    return res;
}
