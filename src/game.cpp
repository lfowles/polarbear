#include <polarbear/game.hpp>

#include <chrono>
#include <memory>
#include <thread>
#include <iostream>
#include <algorithm>

#include <polarbear/config.hpp>
#include <polarbear/helpers.hpp>

Polarbear::Polarbear(void)
{
    EventDelegate delegate = std::bind(&Polarbear::handle_quit, this, std::placeholders::_1);
    auto hash = EventDelegateHash
            (
                    reinterpret_cast<char*>(&Polarbear::handle_quit),
                    reinterpret_cast<uintptr_t>(this)
            );
    dispatch.Register(EventType::Input, delegate, hash);

    EventDelegate scenechange_delegate = std::bind(&Polarbear::handle_scenechange, this, std::placeholders::_1);
    auto scenechange_hash = EventDelegateHash
            (
                    reinterpret_cast<char*>(&Polarbear::handle_scenechange),
                    reinterpret_cast<uintptr_t>(this)
            );
    dispatch.Register(EventType::SceneChange, scenechange_delegate, scenechange_hash);
}

void Polarbear::Run(void)
{
    using ms = std::chrono::duration<double, std::milli>;
    using clock = std::chrono::steady_clock;
    using time = clock::time_point;
    using std::chrono::duration_cast;

    constexpr ms ms_per_loop = ms(min_loop_duration);

    running = true;
    time previous = clock::now();

    while (running)
    {
        time current = clock::now();
        ms elapsed = current - previous;
        previous = current;

        scenemanager.Update(elapsed);

        dispatch.DispatchAll();

        if (not scene_changes.empty())
        {
            do_scenechange();
        }

        //avg = ((count - 1) * avg + ms(clock::now() - current)) / count;

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

void Polarbear::handle_scenechange(EventPtr &event)
{
    std::cout << "def" << std::endl;

    scene_changes.push_back(event);
}

void Polarbear::do_scenechange(void)
{
    for (auto &event : scene_changes)
    {
        auto input_event = std::dynamic_pointer_cast<SceneChangeEvent>(event);
        std::cout << input_event << std::endl;
        switch (input_event->op)
        {
            case SceneChangeEvent::Operation::Pop:
                scenemanager.PopScene();
                break;
            case SceneChangeEvent::Operation::Push:
                scenemanager.PushScene(input_event->scene);
                break;
            case SceneChangeEvent::Operation::Replace:
                scenemanager.SetScene(input_event->scene);
                break;
        }
    }
    scene_changes.clear();
}

void Polarbear::handle_quit(EventPtr &event)
{
    auto input_event = std::dynamic_pointer_cast<InputEvent>(event);
    if (input_event->key == 'q')
    {
        running = false;
    }
}