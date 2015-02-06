#ifndef _GAME_SYSTEMS_HPP_
#define _GAME_SYSTEMS_HPP_
#include <vector>

#include <iostream>
#include "entity.hpp"
#include "tui/curses.cpp"
class System
{
public:
    virtual void update(std::vector<Entity>& entities, double time_elapsed) = 0;
};

class RenderSystem : public System
{
public:
    RenderSystem(void)
    {
        curses.raw(true);
        curses.echo(false);
        curses.refresh();
    }
    virtual void update(std::vector<Entity>& entities, double time_elapsed)
    {
        for (auto& entity : entities)
        {
            for (auto& component : entity.components)
            {
                if (component->Type() == ComponentType::Drawable)
                {
                    auto drawable = dynamic_cast<DrawableComponent*>(component);
                    curses.stdscr.Write(drawable->c, {drawable->x, drawable->y});
                }
            }
        }
        curses.refresh();
    };
private:
    TUI::Curses curses;
};

#endif // _GAME_SYSTEMS_HPP_