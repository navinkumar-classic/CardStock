/**
* @file CardZone.cpp
 * @brief represents entity that stores a collection of card entities
 *
 * Implementation of an entity that stores a collection of card entities
 *
 * @author Navin Kumar<omnavinyogesh.icc@gmail.com>
 * @date 2025-12-22
 * @version 0.1.0
 * @copyright
 *
 * Change Log:
 * - 2025-12-23: file created ~ Navin Kumar.
 * - 2025-12-23: implemented cardQueue and related functionality ~ Navin Kumar.
 * - 2025-12-24: implemented functionality to serialize/deserialize into JSON ~ Navin Kumar.
 */

#include "../include/CardZone.h"
#include <random>
#include <algorithm>

CardZone::CardZone(bool hiddenGeneral, bool hiddenPlayer):hiddenGeneral(hiddenGeneral), hiddenPlayer(hiddenPlayer), gen(std::random_device{}()) {}

CardZone::CardZone(const json& json):hiddenGeneral(true), hiddenPlayer(true), gen(std::random_device{}()) {
    initFromJson(json);
}

void CardZone::setHiddenGeneral(bool hidden) {
    hiddenGeneral = hidden;
}

void CardZone::setHiddenPlayer(bool hidden) {
    hiddenPlayer = hidden;
}

void CardZone::pushFront(Card &&card) {
    cardQueue.push_front(std::move(card));
}

void CardZone::pushBack(Card&& card) {
    cardQueue.push_back(std::move(card));
}

std::optional<Card> CardZone::popFront() {
    if (cardQueue.empty()) {
        return std::nullopt;
    }

    Card c = cardQueue.front();
    cardQueue.pop_front();

    return c;
}

std::optional<Card> CardZone::popBack() {
    if (cardQueue.empty()) {
        return std::nullopt;
    }

    Card c = cardQueue.back();
    cardQueue.pop_back();

    return c;
}

std::optional<Card> CardZone::popById(int id) {
    for (auto it = cardQueue.begin(); it != cardQueue.end(); ++it) {
        if (it->getId() == id) {
            Card c = *it;
            cardQueue.erase(it);
            return c;
        }
    }

    return std::nullopt;
}

const Card& CardZone::peekFront() const {
    if (cardQueue.empty()) {
        throw std::out_of_range("CardZone is empty");
    }
    return cardQueue.front();
}

const Card& CardZone::peekBack() const {
    if (cardQueue.empty()) {
        throw std::out_of_range("CardZone is empty");
    }
    return cardQueue.back();
}

void CardZone::shuffle() {
    std::shuffle(cardQueue.begin(), cardQueue.end(), gen);
}

void CardZone::initFromJson(const json &json) {
    if (json.contains("hiddenGeneral") && json["hiddenGeneral"].is_boolean()) {
        setHiddenGeneral(json["hiddenGeneral"]);
    }

    if (json.contains("hiddenPlayer") && json["hiddenPlayer"].is_boolean()) {
        setHiddenPlayer(json["hiddenPlayer"]);
    }

    if (json.contains("cards") && json["cards"].is_array()) {
        for (auto& cardJson : json["cards"]) {
            if (cardJson.is_object()) {
                pushBack(std::move(Card(cardJson)));
            }
        }
    }
}

json CardZone::toJson() const {
    json j = json::object();

    std::vector<json> cardJson;

    for (const auto& card : cardQueue) {
        cardJson.push_back(card.toJson());
    }

    j["cards"] = cardJson;
    j["hiddenGeneral"] = hiddenGeneral;
    j["hiddenPlayer"] = hiddenPlayer;

    return j;
}

