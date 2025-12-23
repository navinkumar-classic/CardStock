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
 * - 2025-12-23: implemented cardProperty, cardTags and ability to serialize and deserialize into json ~ Navin Kumar.
 */

#include "../include/Card.h"

#include <iostream>

Card::Card(const json &json) {
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

void Card::printAsJson() {
    json j;

    for (auto &[fst, snd] : cardProperty) {
        std::visit([&](const auto& v){ j[fst] = v; }, snd);
    }

    j["tags"] = cardTags;

    std::cout << j.dump(4) << std::endl;
}

void Card::initFromJson(const json& j) {
    for (auto& [key, value] : j.items()) {
        if (value.is_number_integer())
            cardProperty.set(key, value.get<int>());
        else if (value.is_number_float())
            cardProperty.set(key, value.get<float>());
        else if (value.is_boolean())
            cardProperty.set(key, value.get<bool>());
        else if (value.is_string())
            cardProperty.set(key, value.get<std::string>());
        else if (key == "tags" && value.is_array()) {
            for (auto& tag : value.get<std::vector<std::string>>()) {
                addTag(tag);
            }
        }
    }
}


