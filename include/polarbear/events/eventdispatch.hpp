#ifndef _POLARBEAR_EVENTS_EVENTDISPATCH_HPP_
#define _POLARBEAR_EVENTS_EVENTDISPATCH_HPP_

#include "eventqueue.hpp"

using EventDelegate = std::function<void(EventPtr&)>;
using EventDelegateHash = std::pair<intptr_t, intptr_t>;

class System;
class EventDispatch
{
public:
    void DispatchAll(void);

    void Register(EventType type, System& system);
    void Register(EventType type, EventDelegate& delegate, EventDelegateHash& hash);
    EventDelegateHash Register(EventType type, System& system, std::function<void(System*, EventPtr&)> method);

    void Unregister(EventType type, System& system);
    void Unregister(EventType type, EventDelegateHash& hash);
    void Unregister(EventType type, System &system, std::function<void(System*, EventPtr &)> method);

    void QueueEvent(EventPtr event) { queue.SendEvent(event); };

    void SendEvent(EventPtr event);

    EventDelegateHash GetHash(System& system, std::function<void(System*, EventPtr&)>);
    EventDelegateHash GetHash(std::function<void(System*, EventPtr&)>);

private:
    EventQueue queue;
    std::map<EventType, std::vector<EventDelegate>> dispatch;
    std::map<EventType, std::vector<EventDelegateHash>> delegate_locator;

};

#endif // _POLARBEAR_EVENTS_EVENTDISPATCH_HPP_