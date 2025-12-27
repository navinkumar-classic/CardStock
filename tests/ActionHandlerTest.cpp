#include <gtest/gtest.h>
#include "../include/ActionHandler.h"

std::pair<bool, int> test_cond_1(int x) {
    if (x > 10) return std::make_pair(true, 1);
    return std::make_pair(false, -1);
}

std::pair<bool, int> test_cond_2(int x) {
    if (x > 5) return std::make_pair(true, 1);
    return std::make_pair(false, -1);
}

std::pair<bool, int> test_cond_3(int x) {
    if (x < 10) return std::make_pair(true, 1);
    return std::make_pair(false, -1);
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

    std::vector<std::pair<std::string, int>> res = act.getValidAction();

    auto hasAction = [&](const std::string& name) {
        return std::ranges::find_if(
            res,
            [&](const auto& p) { return p.first == name; }
        ) != res.end();
    };

    EXPECT_EQ(2, res.size());
    EXPECT_TRUE(hasAction("test_2"));
    EXPECT_TRUE(hasAction("test_3"));

}