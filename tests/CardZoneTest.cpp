#include <gtest/gtest.h>
#include "../include/CardZone.h"
#include <fstream>

TEST(CardZoneTest, hiddenProperty) {
    CardZone cz(false, false);

    EXPECT_FALSE(cz.getHiddenGeneral());
    EXPECT_FALSE(cz.getHiddenPlayer());

    cz.setHiddenGeneral(true);
    cz.setHiddenPlayer(true);

    EXPECT_TRUE(cz.getHiddenGeneral());
    EXPECT_TRUE(cz.getHiddenPlayer());
}

TEST(CardZoneTest, initFromJson) {
    std::ifstream f("../example/JSON/CardZone/CardZone_1.json");

    json czj = json::parse(f);
    CardZone cz(czj);

    EXPECT_EQ(czj["hiddenGeneral"], cz.getHiddenGeneral());
    EXPECT_EQ(czj["hiddenPlayer"], cz.getHiddenPlayer());

    EXPECT_EQ(czj["cards"][0], cz.at(0).toJson());
    EXPECT_EQ(czj["cards"][1], cz.at(1).toJson());
    EXPECT_EQ(czj["cards"][2], cz.at(2).toJson());

    EXPECT_EQ(czj["cards"][0], cz.peekFront().toJson());
    EXPECT_EQ(czj["cards"][2], cz.peekBack().toJson());
}

TEST(CardZoneTest, pushPopCard) {
    std::ifstream f("../example/JSON/CardZone/CardZone_1.json");

    json czj = json::parse(f);
    CardZone cz(true, true);

    cz.pushBack(std::move(Card(czj["cards"][0])));
    cz.pushBack(std::move(Card(czj["cards"][1])));
    cz.pushFront(std::move(Card(czj["cards"][2])));

    EXPECT_EQ(czj["cards"][2], cz.peekFront().toJson());
    EXPECT_EQ(czj["cards"][1], cz.peekBack().toJson());
    EXPECT_EQ(czj["cards"][0], cz.at(1).toJson());

    Card c1 = std::move(cz.popFront().value());
    EXPECT_EQ(czj["cards"][2], c1.toJson());

    Card c2 = std::move(cz.popBack().value());
    EXPECT_EQ(czj["cards"][1], c2.toJson());

    EXPECT_EQ(1, cz.size());
    EXPECT_EQ(czj["cards"][0], cz.peekFront().toJson());
    EXPECT_EQ(czj["cards"][0], cz.peekBack().toJson());
}

TEST(CardZoneTest, toJson) {
    std::ifstream f("../example/JSON/CardZone/CardZone_1.json");

    json czj = json::parse(f);
    CardZone cz(czj);

    EXPECT_EQ(czj, cz.toJson());
}
