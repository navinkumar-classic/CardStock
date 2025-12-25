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
 * - 2025-12-24: added functionality to serialize/deserialize into JSON ~ Navin Kumar.
 */

#pragma once
#include <deque>
#include <random>
#include "Card.h"

class CardZone {
    public:
        CardZone(bool hiddenGeneral, bool hiddenPlayer);
        CardZone(const json& json);

        CardZone(CardZone&&) noexcept = default;
        CardZone& operator=(CardZone&&) noexcept = default;
        ~CardZone() = default;

        void setHiddenGeneral(bool hidden);
        bool getHiddenGeneral() const {return hiddenGeneral;}

        void setHiddenPlayer(bool hidden);
        bool getHiddenPlayer() const {return hiddenPlayer;}

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
        const Card& at(const size_t index) { return cardQueue.at(index); }

        void shuffle();

        void initFromJson(const json& json);
        json toJson() const;

    private:
        bool hiddenGeneral;
        bool hiddenPlayer;
        std::deque<Card> cardQueue;
        std::mt19937 gen;

};
