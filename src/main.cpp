#include "game/game.hpp"

int main()
{
/*
    int chr = 0;

    {
        TUI::Curses curses;

        curses.raw(true);
        curses.echo(false);
        auto input = TUI::Input(curses.stdscr);

        while (!input.has_input())
            usleep(1000 * 10);
        chr = input.read();
        auto size = curses.stdscr.Size();
        for (int y = 0; y < size.y; ++y) {
            std::string chrstr(size.x, static_cast<char>(chr));
            curses.stdscr.Write(chrstr, {0,y});
        }
        curses.refresh();

        while (!input.has_input())
            usleep(1000 * 10);
    }
    std::cout <<" got " << chr << std::endl;*/
    SuspendedMagic game;
    game.run();
    return 0;

}