#ifndef _POLARBEAR_SYSTEMS_CURSESINPUT_HPP_
#define _POLARBEAR_SYSTEMS_CURSESINPUT_HPP_

#include <swears/input.hpp>

#include "systems.hpp"

class CursesInputSystem : public System
{
public:
    CursesInputSystem(EventDispatch* dispatch, SystemManager* systems, Swears::Window& window) :
            System(dispatch, systems), input(window) {};

    virtual void update(ms time_elapsed) override;

private:
    Swears::Input input;
};

#endif // _POLARBEAR_SYSTEMS_CURSESINPUT_HPP_