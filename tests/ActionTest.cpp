#include <gtest/gtest.h>
#include "../include/PlayerList.h"
#include "../util/Action.h"
#include <fstream>


TEST(ActionTest, checkSetPlayerState) {
    Player p(1, "navin");

    p.state.set<bool>("test", false);
    EXPECT_FALSE(p.state.get<bool>("test").value());

    Action::setPlayerState(p,"test", true);
    EXPECT_TRUE(p.state.get<bool>("test").value());
}

TEST(ActionTest, checkGoToStartPhase) {
    std::ifstream f("../example/JSON/PlayerList/PlayerList_2.json");
    json j = json::parse(f);

    PlayerList p(j);

    EXPECT_EQ(TurnPhase::Start, p.turnManager.getPhase());

    p.turnManager.nextPhase();
    EXPECT_EQ(TurnPhase::Main, p.turnManager.getPhase());

    Action::goToStartPhase(p);
    EXPECT_EQ(TurnPhase::Start, p.turnManager.getPhase());
}

TEST(ActionTest, checkDrawCardFromDeck) {
    Player p(1, "navin");
    p.zoneMap.addZone("hand", CardZone(false, false));

    CardZoneMap globalZones;
    globalZones.addZone("deck", CardZone(true, false));

    json c1Json = {{"id", 1}};
    json c2Json = {{"id", 2}};
    Card c1(c1Json);
    Card c2(c2Json);

    globalZones.getZone("deck")->pushBack(std::move(c1));
    globalZones.getZone("deck")->pushBack(std::move(c2));

    EXPECT_EQ(globalZones.getZoneSize("deck"), 2);
    EXPECT_EQ(p.zoneMap.getZoneSize("hand"), 0);

    Action::drawCardFromDeck(p, globalZones, "hand", "deck", 1);

    EXPECT_EQ(globalZones.getZoneSize("deck"), 1);
    EXPECT_EQ(p.zoneMap.getZoneSize("hand"), 1);

    Action::drawCardFromDeck(p, globalZones, "hand", "deck", 1);

    EXPECT_EQ(globalZones.getZoneSize("deck"), 0);
    EXPECT_EQ(p.zoneMap.getZoneSize("hand"), 2);
}

TEST(ActionTest, checkPlayCard) {
    Player p(1, "navin");
    p.zoneMap.addZone("hand", CardZone(false, false));

    CardZoneMap globalZones;
    globalZones.addZone("discard", CardZone(false, false));

    json cardJson = {{"id", 101}};
    Card c1(cardJson);

    p.zoneMap.getZone("hand")->pushBack(std::move(c1));

    EXPECT_EQ(p.zoneMap.getZoneSize("hand"), 1);
    EXPECT_EQ(globalZones.getZoneSize("discard"), 0);

    Action::playCard(p, globalZones, "hand", "discard", 101);

    EXPECT_EQ(p.zoneMap.getZoneSize("hand"), 0);
    EXPECT_EQ(globalZones.getZoneSize("discard"), 1);
    EXPECT_EQ(globalZones.getZone("discard")->peekFront().getId(), 101);
}