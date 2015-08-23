#ifndef _POLARBEAR_SYSTEMS_CURSESINPUT_HPP_
#define _POLARBEAR_SYSTEMS_CURSESINPUT_HPP_

#include <bitset>
#include <vector>

#include <swears/input.hpp>

#include "systems.hpp"

struct KeyInput
{
    enum class ArrowKey
    {
        None,
        Up,
        Down,
        Left,
        Right
    };

    KeyInput(void) :
            key(0x00), arrows(ArrowKey::None),
            alt(false), ctrl(false), shift(false)
    {};

    // Base keys
    // Only one will be non-zero
    char key;

    ArrowKey arrows;

    // Modifiers
    bool alt;
    bool ctrl;
    bool shift;

};

struct MouseInput
{

    enum class Action
    {
        Invalid,
        Click,
        DoubleClick,
        TripleClick,
    };

    MouseInput(void) :
            action(Action::Invalid),
            button(0), x(0), y(0),
            alt(false), ctrl(false), shift(false)
    {};

    std::bitset<4> button;
    Action action;

    int x;
    int y;

    // Modifiers
    bool alt;
    bool ctrl;
    bool shift;
};

struct Input
{
    Input(): keyboard() {};

    enum class Type
    {
        Keyboard,
        Mouse
    };

    Type type;

    union {
        KeyInput keyboard;
        MouseInput mouse;
    };

};

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

private:
    std::unique_ptr<InputPoller> poller;
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