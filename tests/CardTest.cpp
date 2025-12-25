#include <gtest/gtest.h>
#include <fstream>
#include "../include/Card.h"

TEST(CardTest, addTags) {
    Card c;

    c.addTag("test");
    EXPECT_TRUE(c.hasTag("test"));
}

TEST(CardTest, removeTags) {
    Card c;

    c.addTag("test");
    EXPECT_TRUE(c.hasTag("test"));

    c.removeTag("test");
    EXPECT_FALSE(c.hasTag("test"));
}


TEST(CardTest, initFromJson) {
    std::ifstream f("../example/JSON/Card/Card_1.json");

    json j = json::parse(f);

    Card c(j);

    EXPECT_TRUE(c.hasTag("fire"));
    EXPECT_TRUE(c.hasTag("spell"));

    EXPECT_EQ(5, c.cardProperty.get<int>("attack"));
    EXPECT_EQ(10, c.cardProperty.get<int>("health"));
    EXPECT_EQ("epic", c.cardProperty.get<std::string>("rarity"));
}

TEST(CardTest, toJson) {
    std::ifstream f("../example/JSON/Card/Card_2.json");
    json j = json::parse(f);

    Card c(j);

    EXPECT_EQ(j, c.toJson());
}