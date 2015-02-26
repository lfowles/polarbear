#ifndef _GAME_CURSESSINGLETON_HPP_
#define _GAME_CURSESSINGLETON_HPP_

#include <memory>
#include <swears/curses.hpp>
//#include "tui/input.hpp"

using CursesPtr = std::shared_ptr<Swears::Curses>;
//using CursesInputPtr = std::shared_ptr<Swears::Input>;
class CursesSingleton
{
    public:
        static CursesPtr& GetCurses(void);
/*        static CursesInputPtr& GetInput(void)
        {
            auto curses = GetCurses();
            if (!input_ptr)
            {
                input_ptr = std::make_shared<Swears::Input>(curses->stdscr);
            }
            return input_ptr;
        };
*/
    private:
        static CursesPtr curses_ptr;
//        static CursesInputPtr input_ptr;
};

#endif // _GAME_CURSESSINGLETON_HPP_
