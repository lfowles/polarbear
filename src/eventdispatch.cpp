#include <polarbear/events/event.hpp>
#include <polarbear/systems/systems.hpp>

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

void EventDispatch::Register(EventType type, std::shared_ptr<EventDelegate> delegate, OriginID id)
{
    dispatch[type].push_back(delegate);
    delegate_locator[type].push_back(id);
}

void EventDispatch::Unregister(EventType type, OriginID id)
{
    auto& ids = delegate_locator[type];
    auto& delegates = dispatch[type];
    auto index = 0;
    for (auto& stored_id : ids)
    {
        if (id == stored_id)
        {
            delegates.erase(delegates.begin()+index);
            ids.erase(ids.begin()+index);
            break;
        }
        index++;
    }
}

void EventDispatch::SendEvent(EventPtr event)
{
    auto& delegates = dispatch[event->type];
    for (auto& delegate : delegates)
    {
        delegate->call(event);
    }
}