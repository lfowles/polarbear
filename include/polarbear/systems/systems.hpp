#ifndef _GAME_SYSTEMS_HPP_
#define _GAME_SYSTEMS_HPP_

#include <bitset>
#include <iostream>
#include <memory>
#include <vector>
#include "../entity.hpp"
#include "../event.hpp"
#include <swears/curses.hpp>
#include <swears/input.hpp>
#include "../cursessingleton.hpp"



#include <polarbear/helpers.hpp>

//class Event;
//using EventPtr = std::shared_ptr<Event>;

class System
{
public:
    System(EventDispatch* dispatch) : dispatch(dispatch) {};
    virtual ~System(void) {};
    virtual void update(std::vector<Entity>& entities, ms time_elapsed) = 0;
    virtual void handle(EventPtr& event) {};
protected:
    EventDispatch* dispatch;
};

class CursesRenderSystem : public System
{
public:
    CursesRenderSystem(EventDispatch* dispatch, double max_render_rate) :
            System(dispatch), ms_per_render(1000.0/max_render_rate), accumulated_time(0.0),
            curses(CursesSingleton::GetCurses())
    {
        // This should rather be set up at the beginning of the game
        curses->raw(true);
        curses->echo(false);
        curses->refresh();
        curses->Cursor(Swears::Curses::Visibility::Invisible);
    }

    virtual void update(std::vector<Entity>& entities, ms time_elapsed)
    {
        accumulated_time += time_elapsed;
        if (accumulated_time > ms_per_render)
        {
            render(entities, ms_per_render);
            accumulated_time = ms(0.0);// -= ms_per_render;
        }
    }

    void render(std::vector<Entity>& entities, ms time_elapsed)
    {
        curses->stdscr.Clear();

        // Draw gui in here? Loop over all widgets and call Draw I guess

        std::vector<std::pair<SpriteComponent*, PositionComponent*>> to_draw;
        for (auto& entity : entities)
        {
            auto pos = dynamic_cast<PositionComponent *>(entity.GetComponent(ComponentType::Position));
            if (pos == nullptr)
            {
                continue;
            }

            auto sprite = dynamic_cast<SpriteComponent *>(entity.GetComponent(ComponentType::Sprite));
            if (sprite != nullptr)
            {
                to_draw.push_back({sprite, pos});
            }

            auto widget = dynamic_cast<WidgetComponent *>(entity.GetComponent(ComponentType::Widget));
            if (widget != nullptr)
            {
                auto size = dynamic_cast<SizeComponent *>(entity.GetComponent(ComponentType::Size));
                if (size != nullptr)
                {
                    auto size_vec = Swears::Vec2{size->x, size->y};
                    auto origin = Swears::Vec2{pos->x, pos->y};
                    widget->child->Draw(origin, size_vec, curses->stdscr);
                }
            }
        }

        std::sort(to_draw.begin(), to_draw.end(),
                [](std::pair<SpriteComponent*, PositionComponent*> a, std::pair<SpriteComponent*, PositionComponent*> b)
                {
                    return b.second->z >= a.second->z;
                }
        );

        auto size = curses->stdscr.Size();
        for (auto& sprite_pair : to_draw)
        {
            auto& sprite = sprite_pair.first;
            auto& pos = sprite_pair.second;

            for (int y = 0; y < sprite->height and y + pos->y <= size.y; y++) {
                for (int x = 0; x < sprite->width and x + pos->x <= size.x; x++) {
                    auto &c = sprite->sprite_chars[y * sprite->width + x];
                    if (c != sprite->transparent_char) {
                        curses->stdscr.Write(c & 0xff, {pos->x + x, pos->y + y});
                    }
                }
            }
        }
        curses->refresh();
    }

private:
    CursesPtr curses;
    ms ms_per_render;
    ms accumulated_time;
};

class CursesInputSystem : public System
{
public:
    CursesInputSystem(EventDispatch* dispatch, Swears::Window& window) :
            System(dispatch), input(window) {};

    virtual void update(std::vector<Entity> &entities, ms time_elapsed)
    {
        while (input.has_input())
        {
            auto event = EventPtr(new InputEvent(input.read()));
            dispatch->QueueEvent(event);
        }
    };

private:
    Swears::Input input;
};

class KeyboardControllerSystem : public System
{
public:
    KeyboardControllerSystem(EventDispatch* dispatch) :
            System(dispatch)
    {
        EventDelegate delegate = std::bind(&KeyboardControllerSystem::HandleInput, this, std::placeholders::_1);
        dispatch->Register(EventType::Input, delegate);
        accumulators.resize(2);
    };

    void HandleInput(EventPtr& event)
    {
        auto input_event = std::dynamic_pointer_cast<InputEvent>(event);

        if (input_event->key < 128 and input_event->key >= 0)
        {
            accumulators[1].set(input_event->key);
        }
    }

    virtual void update(std::vector<Entity> &entities, ms time_elapsed)
    {
        for (auto& entity : entities)
        {
            auto keyboard_movement = dynamic_cast<KeyboardControlledMovementComponent*>(entity.GetComponent(ComponentType::KeyboardControlledMovement));
            if (keyboard_movement == nullptr)
            {
                continue;
            }

            auto pos = dynamic_cast<PositionComponent*>(entity.GetComponent(ComponentType::Position));
            if (pos == nullptr)
            {
                continue;
            }

            // This should really generate movement events that get immediately dispatched using SendEvent!
            // This way AI and players can have MovableComponents that receive Move events
            auto magnitude = keyboard_movement->magnitude;//*time_elapsed.count()/1000;

            if (accumulators[1].test('w'))
            {
                pos->y -= magnitude;
            }

            if (accumulators[1].test('a'))
            {
                pos->x -= magnitude;
            }

            if (accumulators[1].test('s'))
            {
                pos->y += magnitude;
            }

            if (accumulators[1].test('d'))
            {
                pos->x += magnitude;
            }

        }

        // Move new accumulator to old accumulator spot
        if (accumulators[0].any() or accumulators[1].any())
        {
            accumulators.emplace_back();
            accumulators.erase(accumulators.begin());
        }
    }

    // 0 is the old accumulator, 1 is the new accumulator
    std::vector<std::bitset<128>> accumulators;


};

class GameEngineSystem : public System
{

};

#endif // _GAME_SYSTEMS_HPP_


