
#pragma once

#include "../include/Player.h"
#include "../include/PlayerList.h"

namespace Condition {

    template <varTypeName T> std::pair<bool, std::vector<int>> checkPlayerState_NEQ(Player& player, const std::string& stateName, T value) {
        if (player.state.has(stateName)) {
            if (player.state.get<T>(stateName).value() == value) {
                return std::make_pair<bool, std::vector<int>>(false, {-1});
            }
        }
        return std::make_pair<bool, std::vector<int>>(true, {-1});
    }

    template <varTypeName T> std::pair<bool, std::vector<int>> findHandCardsMatchingCardProperty(Player& player, const std::string& handDeck, const Card& card, const std::string& stateName) {
        T deckProp = card.cardProperty.get<T>(stateName).value();

        std::vector<int> res = {};
        for (const auto& c: *player.zoneMap.getZone(handDeck)) {
            T colorProp = c.cardProperty.get<T>(stateName).value();

            if (colorProp == deckProp) {
                res.push_back(c.getId());
            }
        }

        if (!res.empty()) {
            return std::make_pair<bool, std::vector<int>>(true, std::move(res));
        }

        return std::make_pair<bool, std::vector<int>>(false, {-1});
    }

    std::pair<bool, std::vector<int>> togglePlayerStateIfEqualAndFail(Player& player, const std::string& stateName, bool value);
    std::pair<bool, std::vector<int>> togglePlayerStateIfEqualAndPass(Player& player, const std::string& stateName, bool value);

    std::pair<bool, std::vector<int>> mergeResultsOr(const std::vector<std::pair<bool, std::vector<int>>>& results);
}