/**
* @file Card.h
 * @brief represents the card entity
 *
 * Header file containing the card entity
 *
 * @author Navin Kumar<omnavinyogesh.icc@gmail.com>
 * @date 2025-12-22
 * @version 0.1.0
 * @copyright
 *
 * Change Log:
 * - 2025-12-22: file created ~ Navin Kumar.
 * - 2025-12-23: added cardProperty, cardTags and ability to serialize and deserialize into JSON ~ Navin Kumar.
 * - 2025-12-23: prevented compiler from copying the card ~ Navin Kumar.
 */
#pragma once
#include "GameState.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;
#include <set>

class Card {
    public:
        Card() = default;
        Card(const json& json);

        ~Card() = default;

        GameState cardProperty;

        void addTag(const std::string& tag);
        bool hasTag(const std::string& tag) const;
        bool removeTag(const std::string& tag);

        Card(const Card&) = delete;
        Card& operator=(const Card&) = delete;

        Card(Card&&) = default;
        Card& operator=(Card&&) = default;

        void initFromJson(const json& json);
        json toJson() const;

    private:
        std::set<std::string> cardTags;
};
