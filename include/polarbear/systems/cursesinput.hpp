#ifndef _POLARBEAR_SYSTEMS_CURSESINPUT_HPP_
#define _POLARBEAR_SYSTEMS_CURSESINPUT_HPP_

#include <vector>

#include <swears/input.hpp>

#include "input.hpp"
#include "systems.hpp"

class InputPoller
{
public:
    virtual std::vector<Input> poll(void) = 0;
};

class CursesInputPoller : public InputPoller
{
public:
    CursesInputPoller(Swears::Window& window) :
            input(window) {};

    virtual std::vector<Input> poll(void) override;

private:
    Swears::Input input;
};

class InputSystem : public System
{
public:
    InputSystem(EventDispatch* dispatch, SystemManager* systems, std::unique_ptr<InputPoller>&& poller) :
            System(dispatch, systems), poller(std::move(poller)) {};

    virtual void update(ms time_elapsed) override;
    virtual void entity_added(std::shared_ptr<Entity>& entity) override;

private:
    std::unique_ptr<InputPoller> poller;
    std::vector<Input> pending_inputs;
    std::vector<std::shared_ptr<Entity>> mouse_entities;
    std::vector<std::shared_ptr<Entity>> keyboard_entities;

};

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