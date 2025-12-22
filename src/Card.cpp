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
 */

#include "../include/Card.h"

void Card::addTag(const std::string &tag) {
    cardTags.insert(tag);
}

bool Card::hasTag(const std::string &tag) const {
    return cardTags.contains(tag);
}

bool Card::removeTag(const std::string &tag) {
    return cardTags.erase(tag) > 0;
}


