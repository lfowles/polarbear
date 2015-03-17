#ifndef _POLARBEAR_EVENTS_EVENT_HPP_
#define _POLARBEAR_EVENTS_EVENT_HPP_

#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <queue>
#include <vector>
#include <stdexcept>

using EventType = unsigned int;

class Event
{
public:
    virtual ~Event() {};
    virtual EventType Type(void) const = 0;
};

template <typename T>
class BaseEvent : public Event
{
public:
    virtual EventType Type(void) const override { return type; };
    static const EventType type;
};

extern EventType nextEventType;
template <typename T> const unsigned int BaseEvent<T>::type(nextEventType++);

class NopEvent : public BaseEvent<NopEvent> {};

class InputEvent : public BaseEvent<InputEvent>
{
public:
    InputEvent(int key) :
            key(key) {};
    int key;
};

class Scene;
using ScenePtr = std::shared_ptr<Scene>;
class SceneChangeEvent : public BaseEvent<SceneChangeEvent>
{
public:
    enum class Operation
    {
        Push,
        Pop,
        Replace
    };
    SceneChangeEvent(Operation op, ScenePtr scene) :
            op(op), scene(scene) {};

    Operation op;
    ScenePtr scene;
};

using EventPtr = std::shared_ptr<Event>;


#endif //_POLARBEAR_EVENTS_EVENT_HPP_