#include <gtest/gtest.h>
#include "../include/PlayerList.h"
#include "../util/Action.h"
#include <fstream>

#include "../util/Condition.h"

TEST(ConditionTest, checkMergeResultsOr) {
    std::pair<bool, std::vector<int>> r1 = {true, {1,2,3}};
    std::pair<bool, std::vector<int>> r2 = {false, {-1}};
    std::pair<bool, std::vector<int>> r3 = {true, {4,3}};
    std::pair<bool, std::vector<int>> r4 = {false, {-1}};

    std::pair<bool, std::vector<int>> r5 = {true, {1,2,3,4}};

    EXPECT_EQ(Condition::mergeResultsOr({r2, r4}), r2);
    EXPECT_EQ(Condition::mergeResultsOr({r1, r2, r3}), r5);
}

TEST(ConditionTest, checkPlayerState_NEQ) {
    Player p(1, "navin");

    p.state.set<int>("test", 1);
    EXPECT_FALSE(Condition::checkPlayerState_NEQ(p, "test", 1).first);

    p.state.set<int>("test", 2);
    EXPECT_TRUE(Condition::checkPlayerState_NEQ(p, "test", 1).first);
}

TEST(ConditionTest, togglePlayerStateIfEqualAndFail) {
    Player p(1, "navin");

    p.state.set<bool>("test", true);
    EXPECT_FALSE(Condition::togglePlayerStateIfEqualAndFail(p, "test", true).first);
    EXPECT_FALSE(p.state.get<bool>("test").value());
}

TEST(ConditionTest, togglePlayerStateIfEqualAndPass) {
    Player p(1, "navin");

    p.state.set<bool>("test", true);
    EXPECT_TRUE(Condition::togglePlayerStateIfEqualAndPass(p, "test", true).first);
    EXPECT_FALSE(p.state.get<bool>("test").value());
}

TEST(ConditionTest, checkFindHandCardsMatchingCardProperty) {
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

    auto res = Condition::findHandCardsMatchingCardProperty<int>(p, "hand", refCard, "color");
    EXPECT_TRUE(res.first);
    EXPECT_EQ(res.second.size(), 2);
    EXPECT_EQ(res.second[0], 1);
    EXPECT_EQ(res.second[1], 3);

    refCard.cardProperty.set<int>("color", 3);
    auto resEmpty = Condition::findHandCardsMatchingCardProperty<int>(p, "hand", refCard, "color");
    EXPECT_FALSE(resEmpty.first);
}