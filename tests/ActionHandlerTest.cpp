#include <gtest/gtest.h>
#include "../include/ActionHandler.h"

bool test_cond_1(int x) {
    if (x > 10) return true;
    return false;
}

bool test_cond_2(int x) {
    if (x > 5) return true;
    return false;
}

bool test_cond_3(int x) {
    if (x < 10) return true;
    return false;
}

bool test_action() {
    return true;
}

TEST(ActionHandler, addAction) {
    ActionHandler act;

    EXPECT_FALSE(act.execute("test_1"));

    EXPECT_TRUE(act.addAction("test_1", [](){return test_cond_1(10);}, [](){return test_action();}));
    EXPECT_TRUE(act.execute("test_1"));
}

TEST(ActionHandler, disableReassignAction) {
    ActionHandler act;

    EXPECT_FALSE(act.execute("test_1"));

    EXPECT_TRUE(act.addAction("test_1", [](){return test_cond_1(10);}, [](){return test_action();}));
    EXPECT_TRUE(act.execute("test_1"));

    EXPECT_FALSE(act.addAction("test_1", [&](){return test_cond_2(10);}, [](){return test_action();}));
    EXPECT_TRUE(act.execute("test_1"));
}


TEST(ActionHandler, removeAction) {
    ActionHandler act;

    EXPECT_FALSE(act.execute("test_1"));

    EXPECT_TRUE(act.addAction("test_1", [](){return test_cond_1(10);}, [](){return test_action();}));
    EXPECT_TRUE(act.execute("test_1"));

    EXPECT_TRUE(act.removeAction("test_1"));
    EXPECT_FALSE(act.execute("test_1"));
}

TEST(ActionHandler, removeNonExsistanceAction) {
    ActionHandler act;

    EXPECT_FALSE(act.removeAction("test_1"));
}

TEST(ActionHandler, checkValidAction) {

    ActionHandler act;

    const int x = 9;
    act.addAction("test_1", [&](){return test_cond_1(x);}, [](){return test_action();});
    act.addAction("test_2", [&](){return test_cond_2(x);}, [](){return test_action();});
    act.addAction("test_3", [&](){return test_cond_3(x);}, [](){return test_action();});

    std::vector<std::string> res = act.getValidAction();

    EXPECT_EQ(2, res.size());
    EXPECT_TRUE(std::ranges::find(res, "test_2") != res.end());
    EXPECT_TRUE(std::ranges::find(res, "test_3") != res.end());

}