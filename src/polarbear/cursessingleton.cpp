#include <polarbear/cursessingleton.hpp>

CursesPtr& CursesSingleton::GetCurses(void)
{
    if (!curses_ptr)
    {
        curses_ptr = std::make_shared<Swears::Curses>();
    }
    return curses_ptr;
};
CursesPtr CursesSingleton::curses_ptr;
