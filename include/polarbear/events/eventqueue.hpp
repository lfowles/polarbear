#ifndef _POLARBEAR_EVENTS_EVENTQUEUE_HPP_
#define _POLARBEAR_EVENTS_EVENTQUEUE_HPP_

#include "event.hpp"

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

#endif // _POLARBEAR_EVENTS_EVENTQUEUE_HPP_