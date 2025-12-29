#include <gtest/gtest.h>
#include "../include/EventManager.h"

PlayerList players1;
CardZoneMap cardZoneMap1;
GameState gameState1;

TEST(EventManagerTest, addEvent) {
    EventManager em;

    EXPECT_FALSE(em.run(players1, cardZoneMap1, gameState1));

    em.addEvent("testEvent_1", [](PlayerList&, CardZoneMap&, GameState&){return true;}, [](PlayerList&, CardZoneMap&, GameState&){return true;});
    EXPECT_TRUE(em.run(players1, cardZoneMap1, gameState1));

    em.addEvent("testEvent_2", [](PlayerList&, CardZoneMap&, GameState&){return true;}, [](PlayerList&, CardZoneMap&, GameState&){return false;});
    EXPECT_FALSE(em.run(players1, cardZoneMap1, gameState1));
}

TEST(EventManagerTest, disableReassignEvent) {
    EventManager em;

    EXPECT_FALSE(em.run(players1, cardZoneMap1, gameState1));
    EXPECT_TRUE(em.addEvent("testEvent_1", [](PlayerList&, CardZoneMap&, GameState&){return true;}, [](PlayerList&, CardZoneMap&, GameState&){return true;}));
    EXPECT_FALSE(em.addEvent("testEvent_1", [](PlayerList&, CardZoneMap&, GameState&){return true;}, [](PlayerList&, CardZoneMap&, GameState&){return false;}));
}

TEST(EventManagerTest, removeEvent) {
    EventManager em;

    em.addEvent("testEvent", [](PlayerList&, CardZoneMap&, GameState&){return true;}, [](PlayerList&, CardZoneMap&, GameState&){return true;});
    EXPECT_TRUE(em.run(players1, cardZoneMap1, gameState1));

    em.removeEvent("testEvent");
    EXPECT_FALSE(em.run(players1, cardZoneMap1, gameState1));
}