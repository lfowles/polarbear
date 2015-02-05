#ifndef _TUI_HPP_
#define _TUI_HPP_

#include <stdexcept>

struct _win_st;
typedef struct _win_st WINDOW;

namespace TUI
{
    class CursesError : public std::runtime_error
    {
    public:
        CursesError(const std::string& msg) : std::runtime_error::runtime_error(msg) {};
    };

    class Window
    {
    public:
        Window(void) = default;
        Window(WINDOW* win): win(win) {};
        ~Window(void);

        static Window Create(void);

    private:
        WINDOW* win;
    };

    class Curses
    {
    public:
        Curses(void);
        ~Curses(void);
        void pause(void);
        void refresh(void);

    private:
        Window base_window;
    };


}

#endif // _TUI_HPP_