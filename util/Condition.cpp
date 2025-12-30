
#include "Condition.h"
#include <unordered_set>

std::pair<bool, std::vector<int>> Condition::togglePlayerStateIfEqualAndFail(Player& player, const std::string& stateName, bool value) {
    if (player.state.has(stateName)) {
        if (player.state.get<bool>(stateName).value() == value) {
            player.state.set(stateName, !value);
            return std::make_pair<bool, std::vector<int>>(false, {-1});
        }
    }
    return std::make_pair<bool, std::vector<int>>(true, {-1});
}

std::pair<bool, std::vector<int>> Condition::togglePlayerStateIfEqualAndPass(Player& player, const std::string& stateName, bool value) {
    if (player.state.has(stateName)) {
        if (player.state.get<bool>(stateName).value() == value) {
            player.state.set(stateName, !value);
            return std::make_pair<bool, std::vector<int>>(true, {-1});
        }
    }
    return std::make_pair<bool, std::vector<int>>(false, {-1});
}

std::pair<bool, std::vector<int>> Condition::mergeResultsOr(const std::vector<std::pair<bool, std::vector<int>>>& results) {
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