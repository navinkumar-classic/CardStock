#include "../include/EventsParser.h"
#include "../util/Event.h"

void EventsParser::init() {
    eventRegisterMap["any_player_has_empty_deck"] = [](PlayerList& playerList, CardZoneMap&, GameState&, const json& json) {
        if (json.contains("hand_zone_name") && json["hand_zone_name"].is_string()) {
            return Event::anyPlayerHasEmptyDeck(playerList, json["hand_zone_name"].get<std::string>());
        }
        throw std::invalid_argument("hand_zone_name missing from any_player_has_empty_deck event");
        return false;
    };

    effectRegisterMap["game_over"] = [](PlayerList&, CardZoneMap&, GameState& gameState, const json& json) {
        if (json.contains("type") && json["type"] == "game_over") {
            Event::gameOver(gameState);
            return true;
        }
        return false;
    };
}

void EventsParser::parseEvent(EventManager& eventManager, const json& eventJson) {
    for (const auto& event: eventJson) {
        eventManager.addEvent(event["event_name"], [this, event](PlayerList& playerList, CardZoneMap &cardZoneMap, GameState &gameState) {
            return eventRegisterMap.at(event["event"]["type"])(playerList, cardZoneMap, gameState, event["event"]);
        },[this, event](PlayerList &playerList, CardZoneMap &cardZoneMap, GameState &gameState) {

            for (const auto& effect: event["effects"]) {
                effectRegisterMap.at(effect["type"])(playerList, cardZoneMap, gameState, effect);
            }
            return true;
        });
    }
}
