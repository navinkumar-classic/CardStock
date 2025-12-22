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
 */
#pragma once
#include "GameState.h"
#include <set>

class Card {
    public:
        Card() = default;
        ~Card() = default;

        GameState cardProperty;

        void addTag(const std::string& tag);

        bool hasTag(const std::string& tag) const;

        bool removeTag(const std::string& tag);

    private:
        std::set<std::string> cardTags;
};
