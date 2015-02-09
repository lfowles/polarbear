#ifndef _TUI_CURSES_HPP_
#define _TUI_CURSES_HPP_

#include "window.hpp"

namespace TUI
{
    class Curses
    {
    public:
        enum class Visibility
        {
            Invisible = 0,
            Normal = 1,
            VeryVisible = 2
        };
        Curses(void);
        ~Curses(void);
        void pause(void);
        void refresh(void);
        void echo(bool enable);
        void raw(bool enable);
        void cursor(Visibility level);

        Window stdscr;
    };
}

#endif // _TUI_CURSES_HPP_