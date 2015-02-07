#include "game.hpp"

#include <chrono>
#include <memory>
#include <thread>
#include <iostream>
#include <algorithm>

#include "helpers.hpp"

void SuspendedMagic::Init(void)
{
    systems.SetMaxUpdateRate(UPDATE_HZ);

    auto rendering_system = std::unique_ptr<System>(new RenderSystem(RENDER_HZ));
    systems.AddSystem(rendering_system);

    Entity a, b, c;
    DrawableComponent d('|', 20, 20);
    a.components.push_back(d);
    systems.AddEntity(a);

    DrawableComponent e('_', 21, 20);
    b.components.push_back(e);
    systems.AddEntity(b);

    DrawableComponent f('|', 22, 20);
    c.components.push_back(f);
    systems.AddEntity(c);
}

void SuspendedMagic::Run(void)
{
    using ms = std::chrono::duration<double, std::milli>;
    using clock = std::chrono::steady_clock;
    using time = clock::time_point;
    using std::chrono::duration_cast;

    constexpr ms ms_per_loop = ms(1000.0/MAXIMUM_HZ);

    running = true;
    time previous = clock::now();

    int ctr = 0;
    double arr[100000];
    while (running)
    {
        time current = clock::now();
        ms elapsed = current - previous;
        previous = current;

        // processInput();

        systems.update(elapsed);


        ms sleep_time = ms_per_loop - duration_cast<ms>(clock::now() - current);
        if (sleep_time.count() > 0)
        {
            std::this_thread::sleep_for(sleep_time);
//            auto block_for = timeval{0, static_cast<long int>(sleep_time.count()*1000)};
//            fd_set readfds;
//            FD_ZERO(&readfds);
//            FD_SET(STDIN_FILENO, &readfds);
//            select(STDIN_FILENO+1, &readfds, nullptr, nullptr, &block_for);
        }
        arr[ctr] = elapsed.count();
        if (++ctr > 100000)
        {
            running = false;
        }
    }
}