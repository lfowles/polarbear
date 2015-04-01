#ifndef _POLARBEAR_SYSTEMS_CURSESRENDER_HPP_
#define _POLARBEAR_SYSTEMS_CURSESRENDER_HPP_

#include "../cursessingleton.hpp"

#include "systems.hpp"

class CursesRenderSystem : public System
{
public:
    CursesRenderSystem(EventDispatch* dispatch, SystemManager* systems, s render_time);
    virtual void update(ms time_elapsed) override;
    void render(ms time_elapsed);

private:
    CursesPtr curses;
    ms ms_per_render;
    ms accumulated_time;
};

#endif // _POLARBEAR_SYSTEMS_CURSESRENDER_HPP_