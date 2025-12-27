/**
* @file Card.cpp
 * @brief represents the card entity
 *
 * Implementing a card entity
 *
 * @author Navin Kumar<omnavinyogesh.icc@gmail.com>
 * @date 2025-12-22
 * @version 0.1.0
 * @copyright
 *
 * Change Log:
 * - 2025-12-22: file created ~ Navin Kumar.
 * - 2025-12-23: implemented cardProperty, cardTags and ability to serialize and deserialize into JSON ~ Navin Kumar.
 */

#include "../include/Card.h"

#include <iostream>

Card::Card(const json &json): id(-1) {
    initFromJson(json);
}

void Card::addTag(const std::string &tag) {
    cardTags.insert(tag);
}

bool Card::hasTag(const std::string &tag) const {
    return cardTags.contains(tag);
}

bool Card::removeTag(const std::string &tag) {
    return cardTags.erase(tag) > 0;
}

json Card::toJson() const{
    json j = json::object();

    j["cardProperty"] = cardProperty.toJson();
    j["tags"] = cardTags;
    j["id"] = id;

    return j;
}

void Card::initFromJson(const json& j) {

    if (j.contains("cardProperty") && j["cardProperty"].is_object()) {
        cardProperty.initFromJson(j["cardProperty"]);
    }

    if (j.contains("tags") && j["tags"].is_array()) {
        for (auto& tag : j["tags"].get<std::vector<std::string>>()) {
            addTag(tag);
        }
    }

    if (j.contains("id") && j["id"].is_number_integer()) {
        id = j["id"];
    }
    else {
        throw std::invalid_argument("Invalid json provided - card id missing");
    }
}


