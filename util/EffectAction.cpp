
#include "EffectAction.h"

void EffectAction::Game_::gameOver(GameState& gameState) {
    gameState.set<bool>("isRunning", false);
}



void EffectAction::TurnManager_::restartTurn(PlayerList &players) {
    players.turnManager.restartTurn();
}

void EffectAction::TurnManager_::reverseTurn(PlayerList &players) {
    players.turnManager.reverseTurn();
}

void EffectAction::TurnManager_::skipTurn(PlayerList &players, int skipCount) {
    players.turnManager.skipTurn(skipCount);
}



void EffectAction::Card_::playCard(Player &player, CardZoneMap &cardZoneMap, const std::string& handName, const std::string& deckName, int cardId) {
    Card temp = player.zoneMap.getZone(handName)->popById(cardId).value();
    cardZoneMap.getZone(deckName)->pushFront(std::move(temp));
}

void EffectAction::Card_::drawCards(Player &player, CardZoneMap &cardZoneMap, const std::string& handName, const std::string& deckName, int numCards) {
    for (int i = 0; i < numCards; i++) {
        Card temp = cardZoneMap.getZone(deckName)->popFront().value();
        player.zoneMap.getZone(handName)->pushBack(std::move(temp));
    }
}



Player& EffectAction::Player_::getCurrentPlayer(PlayerList& playerList) {
    return playerList.getCurrentPlayer();
}
