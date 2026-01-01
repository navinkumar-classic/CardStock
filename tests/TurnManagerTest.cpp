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

    tm.endTurn();
    EXPECT_EQ(tm.getPhase(), TurnPhase::Start);
    EXPECT_EQ(tm.getCurrentPlayerIndex(), 1);
    EXPECT_EQ(tm.getTurnNumber(), 2);

    EXPECT_TRUE(tm.isPlayersTurn(1));
    EXPECT_FALSE(tm.isPlayersTurn(0));
}

TEST(TurnManagerTest, checkReverse) {
    TurnManager tm;

    tm.init(4);

    tm.nextPhase();tm.nextPhase();tm.endTurn();

    EXPECT_EQ(tm.getPhase(), TurnPhase::Start);
    EXPECT_EQ(tm.getCurrentPlayerIndex(), 1);

    tm.nextPhase();tm.nextPhase();tm.endTurn();

    EXPECT_EQ(tm.getPhase(), TurnPhase::Start);
    EXPECT_EQ(tm.getCurrentPlayerIndex(), 2);

    tm.reverseTurn();

    tm.nextPhase();tm.nextPhase();tm.endTurn();

    EXPECT_EQ(tm.getPhase(), TurnPhase::Start);
    EXPECT_EQ(tm.getCurrentPlayerIndex(), 1);

    tm.nextPhase();tm.nextPhase();tm.endTurn();

    EXPECT_EQ(tm.getPhase(), TurnPhase::Start);
    EXPECT_EQ(tm.getCurrentPlayerIndex(), 0);

    tm.nextPhase();tm.nextPhase();tm.endTurn();

    EXPECT_EQ(tm.getPhase(), TurnPhase::Start);
    EXPECT_EQ(tm.getCurrentPlayerIndex(), 3);

}

TEST(TurnManagerTest, checkSkip) {
    TurnManager tm;

    tm.init(4);

    EXPECT_EQ(tm.getPhase(), TurnPhase::Start);
    EXPECT_EQ(tm.getCurrentPlayerIndex(), 0);

    tm.skipTurn(2);
    tm.nextPhase();tm.nextPhase();tm.endTurn();

    EXPECT_EQ(tm.getPhase(), TurnPhase::Start);
    EXPECT_EQ(tm.getCurrentPlayerIndex(), 3);

    tm.nextPhase();tm.nextPhase();tm.endTurn();

    EXPECT_EQ(tm.getPhase(), TurnPhase::Start);
    EXPECT_EQ(tm.getCurrentPlayerIndex(), 0);

    tm.reverseTurn();
    tm.skipTurn(1);
    tm.nextPhase();tm.nextPhase();tm.endTurn();

    EXPECT_EQ(tm.getPhase(), TurnPhase::Start);
    EXPECT_EQ(tm.getCurrentPlayerIndex(), 2);
}

TEST(TurnManagerTest, checkRestart) {
    TurnManager tm;

    tm.init(4);

    tm.restartTurn();
    tm.nextPhase();tm.nextPhase();tm.endTurn();

    EXPECT_EQ(tm.getPhase(), TurnPhase::Start);
    EXPECT_EQ(tm.getCurrentPlayerIndex(), 0);

    tm.nextPhase();tm.nextPhase();tm.endTurn();

    EXPECT_EQ(tm.getPhase(), TurnPhase::Start);
    EXPECT_EQ(tm.getCurrentPlayerIndex(), 1);
}

TEST(TurnManagerTest, checkNextIthPlayerIndex) {
    TurnManager tm;

    tm.init(4);

    EXPECT_EQ(tm.getPhase(), TurnPhase::Start);
    EXPECT_EQ(tm.getCurrentPlayerIndex(), 0);

    EXPECT_EQ(tm.getNextIthPlayerIndex(2), 2);

    tm.reverseTurn();
    EXPECT_EQ(tm.getNextIthPlayerIndex(3), 1);

}

TEST(TurnManagerTest, checkPreviousIthPlayerIndex) {
    TurnManager tm;

    tm.init(4);

    EXPECT_EQ(tm.getPhase(), TurnPhase::Start);
    EXPECT_EQ(tm.getCurrentPlayerIndex(), 0);

    EXPECT_EQ(tm.getPreviousIthPlayerIndex(2), 2);

    tm.reverseTurn();
    EXPECT_EQ(tm.getPreviousIthPlayerIndex(3), 3);

}


