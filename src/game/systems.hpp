#ifndef _GAME_SYSTEMS_HPP_
#define _GAME_SYSTEMS_HPP_

#include <iostream>
#include <memory>
#include <vector>
#include "entity.hpp"
#include "event.hpp"
#include "tui/curses.hpp"
#include "tui/input.hpp"

#include "helpers.hpp"

class Event;
using EventPtr = std::shared_ptr<Event>;

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
            System(dispatch), ms_per_render(1000.0/max_render_rate), accumulated_time(0.0)
    {
        curses.raw(true);
        curses.echo(false);
        curses.refresh();
        curses.cursor(TUI::Curses::Visibility::Invisible);
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
        for (auto& entity : entities)
        {
            for (auto& component : entity.components)
            {
                if (component->Type() == ComponentType::Drawable)
                {
                    auto drawable = dynamic_cast<DrawableComponent*>(component.get());
                    curses.stdscr.Write(drawable->c, {drawable->x, drawable->y});
                }
            }
        }
        curses.refresh();
    }

    TUI::Window& Stdscr(void)
    {
        return curses.stdscr;
    }

private:
    TUI::Curses curses;
    ms ms_per_render;
    ms accumulated_time;
};

class CursesInputSystem : public System
{
public:
    CursesInputSystem(EventDispatch* dispatch, TUI::Window& window) :
            System(dispatch), input(window) {};

    virtual void update(std::vector<Entity> &entities, ms time_elapsed)
    {
        while (input.has_input())
        {
            dispatch->QueueEvent(std::make_shared<InputEvent>(new InputEvent(input.read())));
        }
    };
private:
    TUI::Input input;
};

class GameEngineSystem : public System
{

};

#endif // _GAME_SYSTEMS_HPP_


