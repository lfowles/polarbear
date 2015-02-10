#include "game.hpp"

#include <chrono>
#include <memory>
#include <thread>
#include <iostream>
#include <algorithm>

#include "helpers.hpp"

void SuspendedMagic::Init(void)
{
    EventDelegate delegate = std::bind(&SuspendedMagic::handle_quit, this, std::placeholders::_1);
    dispatch.Register(EventType::Input, delegate);
    systems.SetMaxUpdateRate(UPDATE_HZ);

    auto rendering_system = new CursesRenderSystem(&dispatch, RENDER_HZ);
    systems.AddSystem(std::unique_ptr<System>(rendering_system));

    auto input_system = new CursesInputSystem(&dispatch, rendering_system->Stdscr());
    //systems.AddSystem(std::unique_ptr<System>(input_system));
    systems.AddSystem(input_system);

    Entity a, b, c;
    auto d = std::unique_ptr<Component>(new DrawableComponent ('|', 20, 20));
    a.AddComponent(d);
    systems.AddEntity(a);

    auto e = std::unique_ptr<Component>(new DrawableComponent('_', 21, 20));
    b.AddComponent(e);
    systems.AddEntity(b);

    auto f = std::unique_ptr<Component>(new DrawableComponent('|', 22, 20));
    c.AddComponent(f);
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

    while (running)
    {
        time current = clock::now();
        ms elapsed = current - previous;
        previous = current;

        // processInput();

        systems.update(elapsed);

        try
        {
            dispatch.DispatchAll();
        } catch (EndGame& e) {
            running = false;
        }

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
    auto input_event = std::dynamic_pointer_cast<InputEvent>(event);
    if (input_event->key == (int)'q')
    {
        running = false;
    }
}
