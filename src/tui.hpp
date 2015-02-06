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
        Window(void): win(nullptr) {};
        Window(WINDOW* win): win(win) {};
        Window(Window&& other) { win = other.win; other.win = nullptr; };
        Window& operator=(const Window& other) = delete;
        Window& operator=(Window&& other) { win = other.win; other.win = nullptr; };
        ~Window(void);
        operator WINDOW*() { return win; };

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
        void echo(bool enable);
        void keypad(bool enable);
        void raw(bool enable);


    private:
        Window base_window;
    };


}

#endif // _TUI_HPP_
