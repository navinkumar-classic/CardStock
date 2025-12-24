#include <gtest/gtest.h>
#include "../include/nlohmann/json.hpp"

#include "../include/CardZoneMap.h"
#include "../include/CardZone.h"
#include "../include/Card.h"

using json = nlohmann::json;


TEST(CardZoneMapTest, AddAndGetZone) {
    CardZoneMap zoneMap;

    CardZone hand(false);
    EXPECT_TRUE(zoneMap.addZone("hand", std::move(hand)));

    CardZone* retrieved = zoneMap.getZone("hand");
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->size(), 0);
}

TEST(CardZoneMapTest, HasZone) {
    CardZoneMap zoneMap;

    EXPECT_FALSE(zoneMap.hasZone("deck"));

    zoneMap.addZone("deck", CardZone(true));
    EXPECT_TRUE(zoneMap.hasZone("deck"));
}

TEST(CardZoneMapTest, GetZoneSizeEmpty) {
    CardZoneMap zoneMap;
    zoneMap.addZone("discard", CardZone(false));

    EXPECT_EQ(zoneMap.getZoneSize("discard"), 0);
    EXPECT_EQ(zoneMap.getZoneSize("nonexistent"), 0);
}

// ---------- insertion & deletion -----------

TEST(CardZoneMapTest, AddCardTop) {
    CardZoneMap zoneMap;
    zoneMap.addZone("hand", CardZone(false));

    Card c;
    EXPECT_TRUE(zoneMap.addCardTop("hand", std::move(c)));

    EXPECT_EQ(zoneMap.getZoneSize("hand"), 1);
}

TEST(CardZoneMapTest, AddCardBottom) {
    CardZoneMap zoneMap;
    zoneMap.addZone("deck", CardZone(true));

    Card c1;
    Card c2;

    EXPECT_TRUE(zoneMap.addCardBottom("deck", std::move(c1)));
    EXPECT_TRUE(zoneMap.addCardBottom("deck", std::move(c2)));

    EXPECT_EQ(zoneMap.getZoneSize("deck"), 2);
}

// ---------- json stuff ------------
TEST(CardZoneMapTest, InitFromJson) {
    auto j = R"(
    {
        "hand": {
            "hiddenGeneral": false,
            "hiddenPlayer": true,
            "cards": [
                {
                    "cardProperty": { "attack": 3 },
                    "tags": ["melee"]
                }
            ]
        }
    }
    )"_json;

    CardZoneMap zoneMap;
    zoneMap.initFromJson(j);

    ASSERT_TRUE(zoneMap.hasZone("hand"));

    auto out = zoneMap.toJson();

    EXPECT_FALSE(out["hand"]["hiddenGeneral"].get<bool>());
    EXPECT_TRUE(out["hand"]["hiddenPlayer"].get<bool>());

    EXPECT_EQ(j, out);
}

TEST(CardZoneMapTest, ToJson) {
    auto j = R"(
    {
        "hand": {
            "hiddenGeneral": false,
            "hiddenPlayer": true,
            "cards": [
                {
                    "cardProperty": { "attack": 3 },
                    "tags": ["melee"]
                }
            ]
        }
    }
    )"_json;

    CardZoneMap zoneMap;
    zoneMap.initFromJson(j);

    json out = zoneMap.toJson();

    EXPECT_EQ(j, out);
}

