#include "event.hpp"
#include "systems.hpp"

void EventDispatch::DispatchAll(void)
{
    while (!queue.Empty())
    {
        // Will create the empty vector if it doesn't exist,
        // but there are a fixed number of event types, so this is OK
        auto evt_type = queue.Peek();
        auto event = queue.GetNextEvent();
        if (evt_type == EventType::Input)
        {
            auto input_event = std::static_pointer_cast<InputEvent>(event);
            if (input_event->key == (int)'q')
            {
                throw(EndGame("Stop the game."));
            }
        }
        auto systems = dispatch[evt_type];
        for (auto& system : systems)
        {
            system->handle(event);
        }
    }
}

// Taking a raw pointer here. System will have to make sure to call Unregister on destruction......
void EventDispatch::Register(EventType type, System* system)
{
    dispatch[type].push_back(system);
}

void EventDispatch::Unregister(EventType type, System* system)
{
    auto pos = std::find(dispatch[type].begin(), dispatch[type].end(), system);
    dispatch[type].erase(pos);
};

void EventDispatch::SendEvent(EventPtr &event)
{
    auto systems = dispatch[event->type];
    for (auto& system : systems)
    {
        system->handle(event);
    }
}
