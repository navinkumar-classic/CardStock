#include <gtest/gtest.h>
#include "../include/EventManager.h"

TEST(EventManagerTest, addEvent) {
    EventManager em;

    EXPECT_FALSE(em.run());

    em.addEvent("testEvent_1", [](){return true;}, [](){return true;});
    EXPECT_TRUE(em.run());

    em.addEvent("testEvent_2", [](){return true;}, [](){return false;});
    EXPECT_FALSE(em.run());
}

TEST(EventManagerTest, disableReassignEvent) {
    EventManager em;

    EXPECT_FALSE(em.run());
    EXPECT_TRUE(em.addEvent("testEvent_1", [](){return true;}, [](){return true;}));
    EXPECT_FALSE(em.addEvent("testEvent_1", [](){return true;}, [](){return false;}));
}

TEST(EventManagerTest, removeEvent) {
    EventManager em;

    em.addEvent("testEvent", [](){return true;}, [](){return true;});
    EXPECT_TRUE(em.run());

    em.removeEvent("testEvent");
    EXPECT_FALSE(em.run());
}