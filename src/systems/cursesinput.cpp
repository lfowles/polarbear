#include <polarbear/systems/cursesinput.hpp>

void CursesInputSystem::update(ms time_elapsed)
{
    while (input.has_input())
    {
        auto event = EventPtr(new InputEvent(input.read()));
        dispatch->QueueEvent(event);
    }
}