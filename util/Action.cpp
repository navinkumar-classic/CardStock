
#include "Action.h"

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

Player& Action::getCurrentPlayer(PlayerList& playerList) {
    return playerList.getCurrentPlayer();
}