#include "window.hpp"

#include <ncurses.h>

using namespace TUI;

Window::~Window(void)
{
    if (win != nullptr)
    {
        ::delwin(win);
    }
}

void Window::Write(char c)
{
    ::waddch(win, c);
}

void Window::Write(char c, const Vec2 &pos)
{
    mvwaddch(win, pos.y, pos.x, c);
}

void Window::Write(const std::string str)
{
    ::waddstr(win, str.c_str());
}

void Window::Write(std::string str, const Vec2 &pos)
{
    mvwaddstr(win, pos.y, pos.x, str.c_str());
}

Vec2 Window::Size(void)
{
    Vec2 size;
    getmaxyx(win, size.y, size.x);
    return size;
}
