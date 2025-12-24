#include <gtest/gtest.h>
#include "../include/Card.h"

TEST(CardTest, addRemoveTags) {
    Card c;

    c.addTag("test");
    EXPECT_TRUE(c.hasTag("test"));

    c.removeTag("test");
    EXPECT_FALSE(c.hasTag("test"));
}

TEST(CardTest, initFromJson) {
    auto j = R"(
    {
        "cardProperty": {
            "attack": 5,
            "health": 10,
            "rarity": "epic"
        },
        "tags": [
            "fire",
            "spell"
        ]
    }
    )"_json;

    Card c(j);

    EXPECT_TRUE(c.hasTag("fire"));
    EXPECT_TRUE(c.hasTag("spell"));

    EXPECT_EQ(5, c.cardProperty.get<int>("attack"));
    EXPECT_EQ(10, c.cardProperty.get<int>("health"));
    EXPECT_EQ("epic", c.cardProperty.get<std::string>("rarity"));
}

TEST(CardTest, toJson) {
    auto j = R"(
    {
        "cardProperty": {
            "attack": 5,
            "health": 10,
            "rarity": "epic"
        },
        "tags": [
            "fire",
            "spell"
        ]
    }
    )"_json;

    Card c(j);

    EXPECT_EQ(j, c.toJson());
}