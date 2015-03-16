#include "gtest/gtest.h"

#include <polarbear/events/eventdispatch.hpp>
#include <polarbear/components/components.hpp>

GTEST_TEST(EventDispatch, CallDelegate)
{
    OriginID id = 0;
    bool pass = false;
    auto callback = [&pass](EventPtr& event)
    {
        pass = true;
    };
    auto delegate = std::make_shared<EventDelegateFunction>(callback);

    IDDispenser dispenser{};

    EventDispatch dispatch{};
    dispatch.Register(EventType::None, delegate, 0);

    auto event = std::make_shared<Event>(EventType::None);
    dispatch.SendEvent(event);

    ASSERT_TRUE(pass);
}

GTEST_TEST(EventDispatch, RemoveDelegate)
{
    OriginID id = 0;
    bool pass = false;
    auto callback = [&pass](EventPtr& event)
    {
        pass = true;
    };
    auto delegate = std::make_shared<EventDelegateFunction>(callback);

    EventDispatch dispatch{};
    dispatch.Register(EventType::None, delegate, 0);
    dispatch.Unregister(EventType::None, 0);

    auto event = std::make_shared<Event>(EventType::None);
    dispatch.SendEvent(event);

    ASSERT_FALSE(pass);
}

GTEST_TEST(EventDispatch, Dispenser)
{
    IDDispenser dispenser{};
    ASSERT_NE(dispenser.dispense(), dispenser.dispense());
}

GTEST_TEST(SpriteComponent, UTF8ReadFromFile)
{
    auto sprite = SpriteComponent(RESOURCE_PATH "intro/splash.sprite");
    for (auto ch : sprite.sprite_chars)
    {
        if (ch == '\n')
        {
            std::cout << std::endl;
        } else {
            std::cout << ch;
        }

    }

}