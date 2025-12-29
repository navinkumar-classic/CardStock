#include <gtest/gtest.h>
#include "../include/PlayerList.h"
#include "../util/Action.h"
#include <fstream>

TEST(ActionTest, checkMergeResultsOr) {
    std::pair<bool, std::vector<int>> r1 = {true, {1,2,3}};
    std::pair<bool, std::vector<int>> r2 = {false, {-1}};
    std::pair<bool, std::vector<int>> r3 = {true, {4,3}};
    std::pair<bool, std::vector<int>> r4 = {false, {-1}};

    std::pair<bool, std::vector<int>> r5 = {true, {1,2,3,4}};

    EXPECT_EQ(Action::mergeResultsOr({r2, r4}), r2);
    EXPECT_EQ(Action::mergeResultsOr({r1, r2, r3}), r5);
}

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

TEST(ActionTest, checkPlayerState_NEQ) {
    Player p(1, "navin");

    p.state.set<int>("test", 1);
    EXPECT_FALSE(Action::checkPlayerState_NEQ(p, "test", 1).first);

    p.state.set<int>("test", 2);
    EXPECT_TRUE(Action::checkPlayerState_NEQ(p, "test", 1).first);
}

TEST(ActionTest, checkAndTogglePlayerStateIfEqual) {
    Player p(1, "navin");

    p.state.set<bool>("test", true);
    EXPECT_FALSE(Action::checkAndTogglePlayerStateIfEqual(p, "test", true).first);
    EXPECT_FALSE(p.state.get<bool>("test").value());
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

TEST(ActionTest, checkFindHandCardsMatchingCardProperty) {
    Player p(1, "navin");
    p.zoneMap.addZone("hand", CardZone(false, false));

    json c1Json = {{"id", 1}};
    Card c1(c1Json);
    c1.cardProperty.set<int>("color", 1);

    json c2Json = {{"id", 2}};
    Card c2(c2Json);
    c2.cardProperty.set<int>("color", 2);

    json c3Json = {{"id", 3}};
    Card c3(c3Json);
    c3.cardProperty.set<int>("color", 1);

    p.zoneMap.getZone("hand")->pushBack(std::move(c1));
    p.zoneMap.getZone("hand")->pushBack(std::move(c2));
    p.zoneMap.getZone("hand")->pushBack(std::move(c3));

    json refCardJson = {{"id", 10}};
    Card refCard(refCardJson);
    refCard.cardProperty.set<int>("color", 1);

    auto res = Action::findHandCardsMatchingCardProperty<int>(p, "hand", refCard, "color");
    EXPECT_TRUE(res.first);
    EXPECT_EQ(res.second.size(), 2);
    EXPECT_EQ(res.second[0], 1);
    EXPECT_EQ(res.second[1], 3);

    refCard.cardProperty.set<int>("color", 3);
    auto resEmpty = Action::findHandCardsMatchingCardProperty<int>(p, "hand", refCard, "color");
    EXPECT_FALSE(resEmpty.first);
}