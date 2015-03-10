#ifndef _POLARBEAR_EVENTS_EVENTDISPATCH_HPP_
#define _POLARBEAR_EVENTS_EVENTDISPATCH_HPP_

#include "eventqueue.hpp"

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

    void QueueEvent(EventPtr event) { queue.SendEvent(event); };

    void SendEvent(EventPtr event);

private:
    EventQueue queue;
    std::map<EventType, std::vector<EventDelegate>> dispatch;
};

#endif // _POLARBEAR_EVENTS_EVENTDISPATCH_HPP_