#ifndef _POLARBEAR_CURSESSINGLETON_HPP_
#define _POLARBEAR_CURSESSINGLETON_HPP_

#include <memory>

#include <swears/curses.hpp>

using CursesPtr = std::shared_ptr<Swears::Curses>;
class CursesSingleton
{
    public:
        static CursesPtr& GetCurses(void);

    private:
        static CursesPtr curses_ptr;
};

#endif // _POLARBEAR_CURSESSINGLETON_HPP_
