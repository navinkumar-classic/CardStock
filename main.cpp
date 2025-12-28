#include <iostream>
#include <fstream>
#include "include/Engine.h"

int main() {
    std::ifstream f("../example/JSON/EngineConfig/EngineConfig_2.json");

    json j = json::parse(f);

    Engine game(j);

    game.actionHandler.addAction("play_card", [](Player &player, CardZoneMap &cardZoneMap, GameState &gameState) {


                                     std::string color_deck = cardZoneMap.getZone("deckOpen")->peekFront().cardProperty.get<std::string>("color").value();
                                     int number_deck = cardZoneMap.getZone("deckOpen")->peekFront().cardProperty.get<int>("number").value();

                                     std::vector<int> res = {};
                                     for (const auto& card: *player.zoneMap.getZone("hand")) {
                                         std::string color_card = card.cardProperty.get<std::string>("color").value();
                                         int number_card = card.cardProperty.get<int>("number").value();

                                         if (color_card == color_deck || number_card == number_deck) {
                                             res.push_back(card.getId());
                                         }
                                     }

                                    if (!res.empty()) {
                                        return std::make_pair<bool, std::vector<int>>(true, std::move(res));
                                    }

                                     return std::make_pair<bool, std::vector<int>>(false, {-1});
                                 }, [](PlayerList& playerList, CardZoneMap& cardZoneMap, GameState& gameState, int cardId) {
                                            size_t ind = playerList.turnManager.getCurrentPlayerIndex();
                                            Card temp = playerList.at(ind).zoneMap.getZone("hand")->popById(cardId).value();

                                            cardZoneMap.getZone("deckOpen")->pushFront(std::move(temp));
                                            return true;
                                 });
    game.run();

    return 0;
}
