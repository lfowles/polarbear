#ifndef _TUI_INPUT_HPP_
#define _TUI_INPUT_HPP_

#include "window.hpp"

namespace TUI
{
    class Input
    {
    public:
        Input(Window &win);
        //void start_loop(void);
        //void shutdown(void);
        int read(void);
        bool has_input(void);

    private:
        //void loop(void);
    };
}

#endif // _TUI_INPUT_HPP_