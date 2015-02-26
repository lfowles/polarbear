#include <game/cursessingleton.hpp>

CursesPtr& CursesSingleton::GetCurses(void)
{
    if (!curses_ptr)
    {
        curses_ptr = std::make_shared<TUI::Curses>();
    }
    return curses_ptr;
};
CursesPtr CursesSingleton::curses_ptr;
