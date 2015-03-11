#include "gtest/gtest.h"

#include <polarbear/events/eventdispatch.hpp>


GTEST_TEST(EventDispatch, CallDelegate)
{
    bool pass = false;
    EventDelegate callback = [&pass](EventPtr& event)
    {
        pass = true;
    };
    EventDispatch dispatch{};
    dispatch.Register(EventType::None , callback);
    auto event = std::make_shared<Event>(EventType::None);
    dispatch.SendEvent(event);

    ASSERT_TRUE(pass);
}

GTEST_TEST(EventDispatch, RemoveDelegate)
{
    bool pass = false;
    EventDelegate callback = [&pass](EventPtr& event)
    {
        pass = true;
    };
    EventDispatch dispatch{};
    dispatch.Register(EventType::None , callback);
    dispatch.Unregister(EventType::None, callback);
    auto event = std::make_shared<Event>(EventType::None);
    dispatch.SendEvent(event);

    ASSERT_FALSE(pass);
}
