#include <iostream>
#include <fstream>

#include "include/Engine.h"
#include "util/Action.h"
#include "util/Event.h"

int main() {
    std::ifstream f("../example/JSON/EngineConfig/EngineConfig_2.json");

    json j = json::parse(f);

    Engine game(j);

    game.actionHandler.addAction("play_card", [](Player &player, CardZoneMap &cardZoneMap, GameState &gameState) {

                                     std::pair<bool, std::vector<int>> r1 = Action::findHandCardsMatchingCardProperty<std::string>(player, "hand", cardZoneMap.getZone("deckOpen")->peekFront(), "color" );
                                     std::pair<bool, std::vector<int>> r2 = Action::findHandCardsMatchingCardProperty<int>(player, "hand", cardZoneMap.getZone("deckOpen")->peekFront(), "number" );

                                     return Action::mergeResultsOr({r1, r2});

                                 }, [](PlayerList& playerList, CardZoneMap& cardZoneMap, GameState& gameState, int cardId) {

                                            Action::playCard(playerList.getCurrentPlayer(), cardZoneMap, "hand", "deckOpen", cardId);
                                            return true;
                                 });

    game.actionHandler.addAction("draw_card", [](Player &player, CardZoneMap &cardZoneMap, GameState &gameState) {

                                     return Action::checkAndTogglePlayerStateIfEqual(player, "drawn", true);
                                 }, [](PlayerList& playerList, CardZoneMap& cardZoneMap, GameState& gameState, int cardId) {

                                            Action::drawCardFromDeck(playerList.getCurrentPlayer(), cardZoneMap, "hand", "deckClose", 1);
                                            Action::setPlayerState<bool>(playerList.getCurrentPlayer(), "drawn", true);
                                            Action::goToStartPhase(playerList);

                                            return true;
                                 });

    game.eventManager.addEvent("game_over", [](PlayerList& playerList, CardZoneMap& cardZoneMap, GameState& gameState) {
        return Event::anyPlayerHasEmptyDeck(playerList, "hand");

    },[](PlayerList& playerList, CardZoneMap& cardZoneMap, GameState& gameState) {
        Event::gameOver(gameState);
        return true;
    });

    game.run();

    return 0;
}
