#include "tui.hpp"

#include <iostream>

using namespace std;

int main()
{
    TUI::Curses curses;

    curses.refresh();
    curses.pause();
    return 0;
}