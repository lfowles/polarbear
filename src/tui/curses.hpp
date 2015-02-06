#ifndef _TUI_CURSES_HPP_
#define _TUI_CURSES_HPP_

#include "window.hpp"

namespace TUI
{
    class Curses
    {
    public:
        Curses(void);
        ~Curses(void);
        void pause(void);
        void refresh(void);
        void echo(bool enable);
        void raw(bool enable);

        Window stdscr;
    };
}

#endif // _TUI_CURSES_HPP_