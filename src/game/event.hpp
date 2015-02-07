#ifndef _GAME_EVENT_HPP_
#define _GAME_EVENT_HPP_

enum class EventType
{
    None,
};

class Event
{
public:
    Event(EventType type): type(type) {};
    EventType type;
};

#endif //_GAME_EVENT_HPP_