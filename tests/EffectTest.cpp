#include <gtest/gtest.h>
#include "../include/GameState.h"
#include "../util/Effect.h"

TEST(EffectTest, checkGameOver) {
    GameState gs;
    gs.set<bool>("isRunning", true);

    EXPECT_TRUE(gs.get<bool>("isRunning").value());
    Effect::gameOver(gs);
    EXPECT_FALSE(gs.get<bool>("isRunning").value());
}
