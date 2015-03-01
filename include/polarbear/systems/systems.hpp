#ifndef _GAME_SYSTEMS_HPP_
#define _GAME_SYSTEMS_HPP_

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
        curses->raw(true);
        curses->echo(false);
        curses->refresh();
        curses->Cursor(Swears::Curses::Visibility::Invisible);
    }

    virtual void update(std::vector<Entity>& entities, ms time_elapsed)
    {
        accumulated_time += time_elapsed;
        while (accumulated_time > ms_per_render)
        {
            render(entities, ms_per_render);
            accumulated_time -= ms_per_render;
        }
    }

    void render(std::vector<Entity>& entities, ms time_elapsed)
    {
        curses->stdscr.Clear();
        for (auto& entity : entities)
        {
            auto sprite = dynamic_cast<SpriteComponent*>(entity.GetComponent(ComponentType::Sprite));
            if (sprite == nullptr)
            {
                continue;
            }

            auto pos = dynamic_cast<PositionComponent*>(entity.GetComponent(ComponentType::Position));
            if (pos == nullptr)
            {
                continue;
            }

            for (int y = 0; y < sprite->height; y++)
            {
                for (int x = 0; x < sprite->width; x++)
                {
                    auto& c = sprite->sprite_chars[y*sprite->width+x];
                    if (c != sprite->transparent_char)
                    {
                        curses->stdscr.Write(c&0xff, {pos->x + x, pos->y + y});
                    }
                }
            }
        }
        curses->refresh();
    }

    Swears::Window& Stdscr(void)
    {
        return curses->stdscr;
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
            System(dispatch), accumulated_time(0.0)
    {
        EventDelegate delegate = std::bind(&KeyboardControllerSystem::HandleInput, this, std::placeholders::_1);
        dispatch->Register(EventType::Input, delegate);
    };
    //std::function<void(EventPtr&)>;

    void HandleInput(EventPtr& event)
    {
        for (auto& entity : *entities)
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
            auto input_event = std::dynamic_pointer_cast<InputEvent>(event);
            auto magnitude = keyboard_movement->magnitude*accumulated_time.count()/1000;

            // Todo: Collect all inputs during a frame and store them in a bitset, so only one of each can be sent per frame.
            switch(input_event->key)
            {
                std::cout << input_event->key << std::endl;
                case 'w':
                    pos->y -= magnitude;
                    break;
                case 'a':

                    pos->x -= magnitude;
                    break;
                case 's':
                    pos->y += magnitude;
                    break;
                case 'd':
                    pos->x += magnitude;
                    break;
                default:
                    break;
            }
        }
        accumulated_time = ms(0.0);
    }

    virtual void update(std::vector<Entity> &entities, ms time_elapsed)
    {
        // Ick, is it safe to store entities like this? I might need to grab a singleton in HandleInput or just make sure all systems have a list of entities.

        this->entities = &entities;
        accumulated_time += time_elapsed;
    }

    std::vector<Entity>* entities;
    ms accumulated_time;

};

class GameEngineSystem : public System
{

};

#endif // _GAME_SYSTEMS_HPP_


