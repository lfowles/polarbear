#ifndef _GAME_SYSTEMS_HPP_
#define _GAME_SYSTEMS_HPP_

#include <iostream>
#include <memory>
#include <vector>
#include <game/entity.hpp>
#include <game/event.hpp>
#include <swears/curses.hpp>
#include <swears/input.hpp>
#include <game/cursessingleton.hpp>



#include <game/helpers.hpp>

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
        curses->cursor(TUI::Curses::Visibility::Invisible);
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
                    curses->stdscr.Write(drawable->c, {drawable->x, drawable->y});
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

class GameEngineSystem : public System
{

};

#endif // _GAME_SYSTEMS_HPP_


