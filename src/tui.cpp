#include "tui.hpp"

#include <iostream>

#include "ncurses.h"

using namespace TUI;

Curses::Curses(void)
{
    WINDOW* win = initscr();
    if (win == nullptr)
    {
        throw CursesError("ncurses failed to initialize, see stderr.");
    }
    base_window = Window(win);

    raw();
    keypad(win, true);
    noecho();
}

Curses::~Curses(void)
{
    endwin();
}

Window Window::Create(void)
{
    return Window();
}

void Curses::pause(void)
{
    std::cout << "pause" << std::endl;
    ::getch();
}

void Curses::refresh(void)
{
    ::refresh();
}

Window::~Window(void)
{
        std::cout << "dest" << std::endl;

    if (win != nullptr)
    {
        delwin(win);
    }

}