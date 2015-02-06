#include "game.hpp"
#include "systemmanager.hpp"

#include <chrono>
#include <thread>
#include <unistd.h>
#include <iostream>
#include <algorithm>

void SuspendedMagic::run()
{
    using ms = std::chrono::duration<double, std::milli>;
    using clock = std::chrono::steady_clock;
    using time = clock::time_point;
    using std::chrono::duration_cast;

    constexpr ms ms_per_update = ms(1000.0/UPDATE_HZ);
    constexpr ms ms_per_render = ms(1000.0/RENDER_HZ);
    constexpr ms ms_per_loop = ms(1000.0/MAXIMUM_HZ);

    running = true;
    time previous = clock::now();
    ms update_lag(0.0);
    ms render_lag(0.0);
    int ctr = 0;
    double arr[100000];
    while (running)
    {
        time current = clock::now();
        ms elapsed = current - previous;
        previous = current;

        update_lag += elapsed;

        // processInput();

        while (update_lag >= ms_per_update)
        {
            // update(elapsed);
            update_lag -= ms_per_update;
        }

        if (render_lag >= ms_per_render)
        {
            // check if_needs_render
            // render(update_lag/ms_per_update);
            render_lag -= ms_per_render;
        }

        ms sleep_time = ms_per_loop - duration_cast<ms>(clock::now() - current);
        if (sleep_time.count() > 0)
        {
            auto block_for = timeval{0, static_cast<long int>(sleep_time.count()*1000)};
            fd_set readfds;
            FD_ZERO(&readfds);
            FD_SET(STDIN_FILENO, &readfds);
            select(STDIN_FILENO+1, &readfds, nullptr, nullptr, &block_for);
        }
        arr[ctr] = elapsed.count();
        if (++ctr > 100000)
        {
            running = false;
        }
    }
}