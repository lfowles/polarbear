#ifndef _GAME_EVENT_HPP_
#define _GAME_EVENT_HPP_

#include <algorithm>
#include <map>
#include <memory>
#include <queue>
#include <vector>
#include <stdexcept>

enum class EventType
{
    None,
    Input,
    EndGame
};

class Event
{
public:
    Event(EventType type): type(type) {};
    EventType type;
};

class InputEvent : public Event
{
public:
    InputEvent(int key) : Event(EventType::Input), key(key) {};
    int key;
};

using EventPtr = std::shared_ptr<Event>;

class EventQueue
{
public:
    EventQueue(void) = default;
    void SendEvent(EventPtr& event) { queue.push(event); };
    EventType Peek(void) { return queue.front()->type; };
    EventPtr GetNextEvent(void)
    {
        auto event = queue.front();
        queue.pop();
        return event;
    };
    bool Empty(void) { return queue.empty(); };

private:
    std::queue<EventPtr> queue;
};

using EndGame = std::runtime_error;

class System;
class EventDispatch
{
public:
    void DispatchAll(void);

    // Taking a raw pointer here. System will have to make sure to call Unregister on destruction......
    void Register(EventType type, System* system);
    // Yeah, don't use this yet.....
    void Unregister(EventType type, System* system);
    void QueueEvent(EventPtr& event) {queue.SendEvent(event); };

    void SendEvent(EventPtr& event);

private:
    EventQueue queue;
    std::map<EventType, std::vector<System*>> dispatch;
};

#endif //_GAME_EVENT_HPP_