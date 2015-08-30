#ifndef _POLARBEAR_SYSTEMS_INPUT_HPP_
#define _POLARBEAR_SYSTEMS_INPUT_HPP_

#include <bitset>

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

#endif // _POLARBEAR_SYSTEMS_INPUT_HPP_