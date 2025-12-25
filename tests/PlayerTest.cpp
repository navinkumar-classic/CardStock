#include <gtest/gtest.h>
#include "../include/Player.h"

TEST(PlayerTest, addIdName) {
    Player p(1, "TestPlayer");

    EXPECT_EQ(1, p.getId());
    EXPECT_EQ("TestPlayer", p.getName());
}