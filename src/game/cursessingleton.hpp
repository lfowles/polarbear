#ifndef _GAME_CURSESSINGLETON_HPP_
#define _GAME_CURSESSINGLETON_HPP_

#include <memory>
#include "tui/curses.hpp"
//#include "tui/input.hpp"

using CursesPtr = std::shared_ptr<TUI::Curses>;
//using CursesInputPtr = std::shared_ptr<TUI::Input>;
class CursesSingleton
{
    public:
        static CursesPtr& GetCurses(void);
/*        static CursesInputPtr& GetInput(void)
        {
            auto curses = GetCurses();
            if (!input_ptr)
            {
                input_ptr = std::make_shared<TUI::Input>(curses->stdscr);
            }
            return input_ptr;
        };
*/
    private:
        static CursesPtr curses_ptr;
//        static CursesInputPtr input_ptr;
};

#endif // _GAME_CURSESSINGLETON_HPP_
