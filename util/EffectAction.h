

#pragma once
#include "../include/PlayerList.h"

namespace EffectAction {

    namespace Game_ {
        void gameOver(GameState& gameState);
        void setWinner(PlayerList& players, int winnerIndex);
        void setGameState(GameState& gameState); //T
    }

    namespace TurnManager_ {
        void skipTurn(PlayerList& players, int skipCount);
        void reverseTurn(PlayerList& players);
        void restartTurn(PlayerList& players);
    }

    namespace Card_ {
        Card& getIthCardFromTop(CardZoneMap& cardZoneMap, const std::string& cardZoneName, int i);
        Card& getIthCardFromBottom(CardZoneMap& cardZoneMap, const std::string& cardZoneName, int i);
        Card& getCardById(CardZoneMap& cardZoneMap, const std::string& cardZoneName, int cardId);

        void transferCard(Player& srcPlayer, Player& dstPlayer, const std::string& srcHandName, const std::string& dstHandName, int cardId);
        void playCard(Player& player, CardZoneMap& cardZoneMap, const std::string& handName, const std::string& deckName, int cardId);

        void transferCards(Player& srcPlayer, Player& dstPlayer, const std::string& srcHandName, const std::string& dstHandName, std::vector<int> cardIndices);
        void playCards(Player& player, CardZoneMap& cardZoneMap, const std::string& handName, const std::string& deckName, std::vector<int> cardIndices);
        void drawCards(Player& player,  CardZoneMap& cardZoneMap, const std::string& handName, const std::string& deckName, int numCards);

        void createCard(CardZoneMap& cardZoneMap, const json& j);
        void destroyCard(CardZoneMap& cardZoneMap, int cardId);

        void setCardProperty(Card& card, const std::string& stateName, int cardId, int value); // T
    }

    namespace Player_ {
        Player& getCurrentPlayer(PlayerList& playerList);
        Player& getNextIthPlayer(PlayerList& playerList);
        Player& getPreviousIthPlayer(Player& playerList);
        Player& getPlayerById(Player& playerList);

        template <varTypeName T> void setPlayerState(Player& player, const std::string& stateName, T value) {
            player.state.set<T>(stateName, value);
        }
    }

    namespace CardZone_ {
        CardZoneMap& getCardZoneFromPlayer(Player& player, const std::string& handName);

        void shuffleDeck(CardZoneMap& cardZoneMap, const std::string& deckName);
        void createDeck(CardZoneMap& cardZoneMap, const json& j);
        void destroyDeck(CardZoneMap& cardZoneMap, const std::string& deckName);
    }

}
