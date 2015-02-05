#include "tui.hpp"

#include <iostream>

//#include <ncurses.h>
using namespace std;

int main()
{
    TUI::Curses curses;

    curses.raw(true);
    curses.keypad(true);
    curses.echo(false);
    curses.refresh();
    curses.pause();
    curses.echo(true);
    curses.raw(false);
/*    trace(TRACE_CALLS);
    WINDOW* win = initscr();
    raw();
    keypad(win, true);
    noecho();
    ::getch();

    echo();
    noraw();
    endwin();*/
    return 0;
}
