/**
* @file CardZone.h
 * @brief represents an entity that stores a collection of card entities
 *
 * Header file containing an entity that stores a collection of card entities
 *
 * @author Navin Kumar<omnavinyogesh.icc@gmail.com>
 * @date 2025-12-22
 * @version 0.1.0
 * @copyright
 *
 * Change Log:
 * - 2025-12-22: file created ~ Navin Kumar.
 * - 2025-12-23: added cardQueue and related functionality ~ Navin Kumar.
 */

#pragma once
#include <deque>
#include <random>
#include "Card.h"

class CardZone {
    public:
        CardZone(bool hidden);
        ~CardZone() = default;

        void setHidden(bool hidden);
        bool getHidden() const {return hidden;}

        GameState cardZoneProperty;

        void pushFront(Card&& card);
        void pushBack(Card&& card);

        std::optional<Card> popFront();
        std::optional<Card> popBack();

        const Card& peekFront() const;
        const Card& peekBack() const;

        bool empty() const {return cardQueue.empty();}
        size_t size() const {return cardQueue.size();}

        auto begin() { return cardQueue.begin(); }
        auto end() { return cardQueue.end(); }

        void shuffle();

    private:
        bool hidden;
        std::deque<Card> cardQueue;
        std::mt19937 gen;

};
