#ifndef _GAME_SYSTEMS_HPP_
#define _GAME_SYSTEMS_HPP_

#include <vector>
#include <iostream>
#include "entity.hpp"
#include "tui/curses.hpp"

#include "helpers.hpp"

class System
{
public:
    virtual void update(std::vector<Entity>& entities, ms time_elapsed) = 0;
};

class RenderSystem : public System
{
public:
    RenderSystem(double max_render_rate) : ms_per_render(1000.0/max_render_rate), accumulated_time(0.0)
    {
//        curses.raw(true);
//        curses.echo(false);
//        curses.refresh();
    }

    virtual void update(std::vector<Entity>& entities, ms time_elapsed)
    {
        accumulated_time += time_elapsed;
        while (accumulated_time > ms_per_render)
        {
            std::cout << "rendere" << std::endl;
            //render(entities, ms_per_render);
            accumulated_time -= ms_per_render;
        }
    };

    void render(std::vector<Entity>& entities, ms time_elapsed)
    {
        for (auto& entity : entities)
        {
            for (auto& component : entity.components)
            {
                if (component.Type() == ComponentType::Drawable)
                {
                    auto drawable = dynamic_cast<DrawableComponent&>(component);
                    //curses.stdscr.Write(drawable.c, {drawable.x, drawable.y});
                }
            }
        }
        //curses.refresh();
    }
private:
    //TUI::Curses curses;
    ms ms_per_render;
    ms accumulated_time;
};

#endif // _GAME_SYSTEMS_HPP_