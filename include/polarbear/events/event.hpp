#ifndef _POLARBEAR_EVENTS_EVENT_HPP_
#define _POLARBEAR_EVENTS_EVENT_HPP_

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
    SceneChange,
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

class Scene;
using ScenePtr = std::shared_ptr<Scene>;
class SceneChangeEvent : public Event
{
public:
    enum class Operation
    {
        Push,
        Pop,
        Replace
    };
    SceneChangeEvent(Operation op, ScenePtr scene) :
            Event(EventType::SceneChange), op(op), scene(scene) {};

    Operation op;
    ScenePtr scene;
};

using EventPtr = std::shared_ptr<Event>;


//using EndGame = std::runtime_error;



#endif //_POLARBEAR_EVENTS_EVENT_HPP_