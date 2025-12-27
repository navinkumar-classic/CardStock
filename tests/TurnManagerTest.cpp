//
// Created by echel on 25/12/2025.
//

#include <gtest/gtest.h>
#include "../include/TurnManager.h"

TEST(TurnManagerTest, basicTurnFlow) {
    TurnManager tm;

    tm.init(2);

    EXPECT_EQ(tm.getCurrentPlayerIndex(), 0);
    EXPECT_EQ(tm.getTurnNumber(), 1);
    EXPECT_EQ(tm.getPhase(), TurnPhase::Start);

    tm.nextPhase();
    EXPECT_EQ(tm.getPhase(), TurnPhase::Main);

    tm.nextPhase();
    EXPECT_EQ(tm.getPhase(), TurnPhase::End);

    tm.nextPhase();
    EXPECT_EQ(tm.getPhase(), TurnPhase::Start);
    EXPECT_EQ(tm.getCurrentPlayerIndex(), 1);
    EXPECT_EQ(tm.getTurnNumber(), 2);

    EXPECT_TRUE(tm.isPlayersTurn(1));
    EXPECT_FALSE(tm.isPlayersTurn(0));
}
