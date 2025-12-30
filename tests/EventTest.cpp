#include <gtest/gtest.h>
#include <fstream>

#include "../include/Player.h"
#include "../util/Event.h"

TEST(EventTest, checkHasEmptyCardZone) {
    std::ifstream f("../example/JSON/Player/Player_1.json");
    json j = json::parse(f);

    Player p(j);

    EXPECT_FALSE(Event::hasEmptyCardZone(p, "hand1"));
    EXPECT_TRUE(Event::hasEmptyCardZone(p, "hand3"));
}

TEST(EventTest, checkAnyPlayerHasEmptyDeck) {
    std::ifstream f("../example/JSON/PlayerList/PlayerList_2.json");
    json j = json::parse(f);

    PlayerList p(j);

    EXPECT_FALSE(Event::anyPlayerHasEmptyDeck(p, "hand2"));
    EXPECT_TRUE(Event::anyPlayerHasEmptyDeck(p, "hand3"));
}

TEST(EventTest, checkAllPlayerHasEmptyDeck) {
    std::ifstream f("../example/JSON/PlayerList/PlayerList_2.json");
    json j = json::parse(f);

    PlayerList p(j);

    EXPECT_FALSE(Event::allPlayersHaveEmptyDeck(p, "hand2"));
    EXPECT_FALSE(Event::allPlayersHaveEmptyDeck(p, "hand3"));
    EXPECT_TRUE(Event::allPlayersHaveEmptyDeck(p, "hand4"));
}