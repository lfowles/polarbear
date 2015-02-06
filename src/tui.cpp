#include "tui.hpp"

#include <iostream>

#include <ncurses.h>

using namespace TUI;

Curses::Curses(void)
{
    //::trace(TRACE_CALLS);
    WINDOW* win = initscr();
    if (win == nullptr)
    {
        throw CursesError("ncurses failed to initialize, see stderr.");
    }
    base_window = Window(win);
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
    ::getch();
}

void Curses::echo(bool enable)
{
    if (enable)
    {
        ::echo();
    } else {
        ::noecho();
    }
}

void Curses::raw(bool enable)
{
    if (enable)
    {
        ::raw();
    } else {
        ::noraw();
    }
}

void Curses::keypad(bool enable)
{
    if (enable)
    {
        ::keypad(base_window, true);
    } else {
        ::keypad(base_window, false);
    }
}

void Curses::refresh(void)
{
    ::refresh();
}

Window::~Window(void)
{
    if (win != nullptr)
    {
        delwin(win);
        win = nullptr;
    }
}
