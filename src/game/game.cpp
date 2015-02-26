#include "game.hpp"

#include <chrono>
#include <memory>
#include <thread>
#include <iostream>
#include <algorithm>

#include "config.hpp"
#include "helpers.hpp"
#include "mainmenuscene.hpp"
void SuspendedMagic::Init(void)
{
    EventDelegate delegate = std::bind(&SuspendedMagic::handle_quit, this, std::placeholders::_1);
    dispatch.Register(EventType::EndGame, delegate);

    //MainMenuScene scene(dispatch);
    scenemanager.PushScene(std::make_shared<MainMenuScene>(dispatch));
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

    while (running)
    {
        time current = clock::now();
        ms elapsed = current - previous;
        previous = current;

        scenemanager.Update(elapsed);

        dispatch.DispatchAll();

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
    }
}

void SuspendedMagic::handle_quit(EventPtr &event)
{
    running = false;
}
