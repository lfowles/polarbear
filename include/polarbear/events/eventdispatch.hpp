#ifndef _POLARBEAR_EVENTS_EVENTDISPATCH_HPP_
#define _POLARBEAR_EVENTS_EVENTDISPATCH_HPP_

#include <functional>

#include "eventqueue.hpp"

// using EventDelegate = std::function<void(EventPtr&)>;
// using EventDelegateHash = std::pair<intptr_t, intptr_t>;

class EventDelegate
{
public:
    virtual ~EventDelegate(void) {};
    virtual void call(EventPtr& event) = 0;
};

template <typename T>
class EventDelegateMemberFunction : public EventDelegate
{
public:
    EventDelegateMemberFunction(T* object, std::function<void(T*, EventPtr&)> fn) : instance(object), function(fn)  {};

    void call(EventPtr& event)
    {
        function(instance, event);
    }
private:
    T* instance;
    std::function<void(T*, EventPtr&)> function;
};

class EventDelegateFunction : public EventDelegate
{
public:
    EventDelegateFunction(std::function<void(EventPtr&)> fn) : function(fn)  {};

    void call(EventPtr& event)
    {
        function(event);
    }
private:
    std::function<void(EventPtr&)> function;
};

using OriginID = int;

class IDDispenser
{
public:
    OriginID dispense(void)
    {
        static int next_id;
        next_id++;
        return next_id;
    }
};

// So, the caveat here is that each origin (class) needs a unique ID and can only store one callback per event type
class System;
class EventDispatch
{
public:
    void DispatchAll(void);

    template <typename T>
    void Register(std::shared_ptr<EventDelegate> delegate, OriginID id)
    {
        static_assert(std::is_base_of<Event, T>::value, "Type must be an Event");
        Register(T::type, delegate, id);
    }
    void Register(EventType type, std::shared_ptr<EventDelegate> delegate, OriginID id);

    template <typename T>
    void Unregister(OriginID id)
    {
        static_assert(std::is_base_of<Event, T>::value, "Type must be an Event");
        Unregister(T::type, id);
    }

    void Unregister(EventType type, OriginID id);

    void UnregisterAll(OriginID id);

    void QueueEvent(EventPtr event) { queue.SendEvent(event); };

    void SendEvent(EventPtr event);

private:
    EventQueue queue;
    std::map<EventType, std::vector<std::shared_ptr<EventDelegate>>> dispatch;
    std::map<EventType, std::vector<OriginID>> delegate_locator;

};

#endif // _POLARBEAR_EVENTS_EVENTDISPATCH_HPP_