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

void EventDispatch::Register(EventType type, System &system)
{
    EventDelegate delegate = std::bind(&System::handle, &system, std::placeholders::_1);
    auto hash = GetHash(system, &System::handle);
    Register(type, delegate, hash);
}

EventDelegateHash EventDispatch::Register(EventType type, System &system, std::function<void(System*, EventPtr &)> method)
{
    auto hash = GetHash(system, method);
    EventDelegate delegate = std::bind(method.target(), &system, std::placeholders::_1);
    Register(type, delegate, hash);
    return hash;
}

void EventDispatch::Register(EventType type, EventDelegate &delegate, EventDelegateHash &hash)
{
    dispatch[type].push_back(delegate);
    delegate_locator[type].push_back(hash);
}

void EventDispatch::Unregister(EventType type, System &system)
{
    EventDelegate delegate = std::bind(&System::handle, &system, std::placeholders::_1);
    auto hash = GetHash(system, &System::handle);
    Unregister(type, hash);
}

void EventDispatch::Unregister(EventType type, System &system, std::function<void(System*, EventPtr &)> method)
{
    auto hash = GetHash(system, method);
    Unregister(type, hash);
}

#include <iostream>
void EventDispatch::Unregister(EventType type, EventDelegateHash &hash)
{
    auto& hashes = delegate_locator[type];
    auto& delegates = dispatch[type];
    auto index = 0;
    for (auto& stored_hash : hashes)
    {
        if (hash == stored_hash)
        {
            delegates.erase(delegates.begin()+index);
            hashes.erase(hashes.begin()+index);
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
        delegate(event);
    }
}

EventDelegateHash EventDispatch::GetHash(System &system, std::function<void(System*, EventPtr&)> function)
{
    return EventDelegateHash{
            reinterpret_cast<EventDelegateHash::first_type>(function.target()),
            reinterpret_cast<EventDelegateHash::second_type>(&system),
    };
}

EventDelegateHash EventDispatch::GetHash(std::function<void(System*, EventPtr&)> function)
{
    return EventDelegateHash{
            reinterpret_cast<EventDelegateHash::first_type>(function.target()),
            EventDelegateHash::second_type{0}
    };
}
