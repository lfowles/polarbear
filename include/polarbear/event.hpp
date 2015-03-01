#ifndef _GAME_EVENT_HPP_
#define _GAME_EVENT_HPP_

#include <algorithm>
#include <functional>
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
    virtual ~Event() {};
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

using EventDelegate = std::function<void(EventPtr&)>;

class System;
class EventDispatch
{
public:
    void DispatchAll(void);

    void Register(EventType type, System& system);
    void Register(EventType type, EventDelegate& delegate);

    void Unregister(EventType type, System& system);
    void Unregister(EventType type, EventDelegate& delegate);

    void QueueEvent(EventPtr& event) {queue.SendEvent(event); };

    void SendEvent(EventPtr& event);

private:
    EventQueue queue;
    std::map<EventType, std::vector<EventDelegate>> dispatch;
//    std::map<EventType, std::vector<System*>> dispatch;
};

#endif //_GAME_EVENT_HPP_