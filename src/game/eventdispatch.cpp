#include "event.hpp"
#include "systems.hpp"

void EventDispatch::DispatchAll(void)
{
    while (!queue.Empty())
    {
        // Will create the empty vector if it doesn't exist,
        // but there are a fixed number of event types, so this is OK
        auto event = queue.GetNextEvent();
        SendEvent(event);
    }
}

void EventDispatch::Register(EventType type, System &system)
{
    EventDelegate delegate = std::bind(&System::handle, &system, std::placeholders::_1);
    Register(type, delegate);
}

void EventDispatch::Register(EventType type, EventDelegate &delegate)
{
    dispatch[type].push_back(delegate);
}

void EventDispatch::Unregister(EventType type, System &system)
{
    EventDelegate delegate = std::bind(&System::handle, &system, std::placeholders::_1);
    Unregister(type, delegate);
}

void EventDispatch::Unregister(EventType type, EventDelegate &delegate)
{
    auto delegates = dispatch[type];
    auto index = 0;
    for (auto stored_delegate : delegates)
    {
        if (delegate.target<void(EventPtr&)>() == stored_delegate.target<void(EventPtr&)>())
        {
            delegates.erase(delegates.begin()+index);
            break;
        }
        index++;
    }
}

void EventDispatch::SendEvent(EventPtr& event)
{
    auto delegates = dispatch[event->type];
    for (auto& delegate : delegates)
    {
        delegate(event);
    }
}
