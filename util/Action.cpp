
#include "Action.h"

std::pair<bool, std::vector<int>> Action::checkAndTogglePlayerStateIfEqual(Player& player, const std::string& stateName, bool value) {
    if (player.state.has(stateName)) {
        if (player.state.get<bool>(stateName).value() == value) {
            player.state.set(stateName, !value);
            return std::make_pair<bool, std::vector<int>>(false, {-1});
        }
    }
    return std::make_pair<bool, std::vector<int>>(true, {-1});
}

void Action::drawCardFromDeck(Player &player, CardZoneMap &cardZoneMap, const std::string& handName, const std::string& deckName, int numCards) {
    for (int i = 0; i < numCards; i++) {
        Card temp = cardZoneMap.getZone(deckName)->popFront().value();
        player.zoneMap.getZone(handName)->pushBack(std::move(temp));
    }
}

void Action::playCard(Player &player, CardZoneMap &cardZoneMap, const std::string& handName, const std::string& deckName, int cardId) {
    Card temp = player.zoneMap.getZone(handName)->popById(cardId).value();
    cardZoneMap.getZone(deckName)->pushFront(std::move(temp));
}

void Action::goToStartPhase(PlayerList& playerList) {
    playerList.turnManager.goToStartPhase();
}

std::pair<bool, std::vector<int>> Action::mergeResultsOr(const std::vector<std::pair<bool, std::vector<int>>>& results) {
    std::vector<int> mergedResults;
    std::unordered_set<int> seen;

    for (const auto& result : results) {
        if (result.first) {
            for (int id : result.second) {
                if (seen.insert(id).second) {
                    mergedResults.push_back(id);
                }
            }
        }
    }

    if (mergedResults.empty()) {
        return std::make_pair<bool, std::vector<int>>(false, {-1});
    }

    return std::make_pair<bool, std::vector<int>>(true, std::move(mergedResults));
}