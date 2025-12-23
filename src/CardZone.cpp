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
 */

#include "../include/CardZone.h"
#include <random>
#include <algorithm>

CardZone::CardZone(bool hidden):hidden(hidden), gen(std::random_device{}()) {}

void CardZone::setHidden(bool hide) {
    hidden = hide;
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

    Card c = std::move(cardQueue.front());
    cardQueue.pop_front();

    return c;
}

std::optional<Card> CardZone::popBack() {
    if (cardQueue.empty()) {
        return std::nullopt;
    }
    Card c = std::move(cardQueue.back());
    cardQueue.pop_back();

    return c;
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

