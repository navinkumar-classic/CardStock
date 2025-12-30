#include "../include/ActionsParser.h"

#include "../util/Action.h"

void ActionsParser::init() {
    conditionRegisterMap["toggle_player_state_if_equal_and_fail"] = [](Player &player, CardZoneMap &cardZoneMap, GameState &gameState, const json &json) {
                if (!json.contains("state") || !json.contains("value") || !json["state"].is_string() || !json["value"].is_boolean()) {
                    throw std::invalid_argument("Incomplete json for toggle_player_state_if_equal_and_fail condition");
                }
                return Action::togglePlayerStateIfEqualAndFail(player, json["state"], json["value"].get<bool>());
            };

    conditionRegisterMap["toggle_player_state_if_equal_and_pass"] = [](Player &player, CardZoneMap &cardZoneMap, GameState &gameState, const json &json) {
        if (!json.contains("state") || !json.contains("value") || !json["state"].is_string() || !json["value"].is_boolean()) {
            throw std::invalid_argument("Incomplete json for toggle_player_state_if_equal_and_pass condition");
            }
        return Action::togglePlayerStateIfEqualAndPass(player, json["state"], json["value"].get<bool>());
    };

    conditionRegisterMap["find_hand_cards_matching_card_property"] = [](Player &player, CardZoneMap &cardZoneMap, GameState &gameState, const json &json) {
        if (!json.contains("hand_name") || !json.contains("deck_name") ||
            !json.contains("state_name") || !json.contains("state_type") ||
            !json.contains("card_location")) {
            throw std::invalid_argument("Incomplete json for find_hand_cards_matching_card_property condition");
        }

        const Card& card = (json["card_location"] == "top") ? cardZoneMap.getZone(json["deck_name"])->peekFront(): cardZoneMap.getZone(json["deck_name"])->peekBack();

        if (json["state_type"] == "string") {
            return Action::findHandCardsMatchingCardProperty<std::string>(player, json["hand_name"], card, json["state_name"]);
        }
        if (json["state_type"] == "int") {
            return Action::findHandCardsMatchingCardProperty<int>(player, json["hand_name"], card, json["state_name"]);
        }
        if (json["state_type"] == "float") {
            return Action::findHandCardsMatchingCardProperty<float>(player, json["hand_name"], card, json["state_name"]);
        }
        if (json["state_type"] == "bool") {
            return Action::findHandCardsMatchingCardProperty<bool>(player, json["hand_name"], card, json["state_name"]);
        }

        throw std::invalid_argument("Unsupported state_type in find_hand_cards_matching_card_property condition");
    };

    conditionRegisterMap["merge_results_or"] = [this](Player &player, CardZoneMap &cardZoneMap, GameState &gameState, const json &json) {
        if (!json.contains("args")||!json["args"].is_array()) {
            throw std::invalid_argument("Incomplete json for merge_results_or condition");
        }
        std::vector<std::pair<bool, std::vector<int>>> res;

        for (const auto& arg: json["args"]) {
            std::pair<bool, std::vector<int>> condRes = conditionRegisterMap[arg["type"]](player, cardZoneMap, gameState, arg);
            res.emplace_back(condRes.first, condRes.second);
        }

        return Action::mergeResultsOr(res);
    };

    actionRegisterMap["go_to_start_phase"] = [](PlayerList &playerList, CardZoneMap &cardZoneMap, GameState &gameState,
                                                int cardId, const json &json) {
        Action::goToStartPhase(playerList);
        return true;
    };

    actionRegisterMap["draw_card_from_deck"] = [](PlayerList &playerList, CardZoneMap &cardZoneMap,
                                                  GameState &gameState, int cardId, const json &json) {
        if (json.contains("hand_name") && json.contains("deck_name") && json.contains("num_cards")) {
            if (json.contains("player") && json["player"].is_string() && json["player"] == "current") {
                Action::drawCardFromDeck(Action::getCurrentPlayer(playerList), cardZoneMap, json["hand_name"],
                                         json["deck_name"], json["num_cards"]);
                return true;
            }
        }
        throw std::invalid_argument("Incomplete json for draw_card_from_deck action");
    };

    actionRegisterMap["set_player_state"] = [](PlayerList &playerList, CardZoneMap &, GameState &, int cardId,
                                               const json &json) {
        if (!json.contains("player") || !json.contains("state") || !json.contains("value")) {
            throw std::invalid_argument("Incomplete json for set_player_state action");
        }

        Player &player = (json["player"].is_string() && json["player"] == "current")
                             ? Action::getCurrentPlayer(playerList)
                             : playerList.at(json["player"].get<size_t>());

        const std::string stateName = json["state"];

        if (json["value"].is_number_integer()) {
            Action::setPlayerState<int>(player, stateName, json["value"].get<int>());
        } else if (json["value"].is_number_float()) {
            Action::setPlayerState<float>(player, stateName, json["value"].get<float>());
        } else if (json["value"].is_boolean()) {
            Action::setPlayerState<bool>(player, stateName, json["value"].get<bool>());
        } else if (json["value"].is_string()) {
            Action::setPlayerState<std::string>(player, stateName, json["value"].get<std::string>());
        } else {
            throw std::invalid_argument(
                "Unsupported value type in set_player_state");
        }

        return true;
    };

    actionRegisterMap["play_card"] = [](PlayerList &playerList, CardZoneMap &cardZoneMap, GameState &gameState, int cardId, const json &json) {
        if (!json.contains("hand_name") || !json.contains("deck_name") || !json.contains("player")) {
            throw std::invalid_argument("Incomplete json for play_card action");
        }
        if (json["player"].is_string() && json["player"] == "current") {
            Action::playCard(Action::getCurrentPlayer(playerList), cardZoneMap, json["hand_name"], json["deck_name"], cardId);
        }
        return true;
    };
}

void ActionsParser::parseAction(ActionHandler &actionHandler, const json &eventJson) {

    for (const auto& event: eventJson) {
        actionHandler.addAction(event["actionName"], [this, event](Player &player, CardZoneMap &cardZoneMap, GameState &gameState) {
            return conditionRegisterMap[event["condition"]["type"]](player, cardZoneMap, gameState, event["condition"]);
        }, [this, event](PlayerList &playerList, CardZoneMap &cardZoneMap, GameState &gameState, int cardId) {

            for (const auto& action: event["actions"]) {
                actionRegisterMap[action["type"]](playerList, cardZoneMap, gameState, cardId, action);
            }

            return true;
        });
    }
}
