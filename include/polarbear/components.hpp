#ifndef _GAME_COMPONENTS_HPP_
#define _GAME_COMPONENTS_HPP_

// instead of a scene graph, have components like "AttachedTo(parent)", etc

#include <string>
#include <vector>
#include <swears/widgets/widget.hpp>

class Component
{
public:
    virtual unsigned int Type(void) const = 0;
    virtual ~Component() = default;

};

// http://www.reddit.com/r/learnprogramming/comments/1jzlon/cwhy_exactly_is_rtti_and_typeid_bad/cbkz2mc
static unsigned int nextType = 0;
template <typename T>
class BaseComponent : public Component
{
public:
    virtual unsigned int Type(void) const override {return type;};
    static const unsigned int type;
};

class PositionComponent : public BaseComponent<PositionComponent>
{
public:
    PositionComponent(float x, float y) : x(x), y(y), z(0.0f) {};
    PositionComponent(float x, float y, float z) : x(x), y(y), z(z) {};
    float x, y, z;
};

class SizeComponent : public BaseComponent<SizeComponent>
{
public:
    SizeComponent(float x, float y) : x(x), y(y) {};
    float x, y;
};


class SpriteComponent : public BaseComponent<SpriteComponent>
{
public:
    SpriteComponent(int w, int h, const std::vector<int>& sprite, int transparent) :
            width(w), height(h),
            sprite_chars(sprite), transparent_char(transparent), attr(0) {};
    SpriteComponent(int c) :
            width(1), height(1),
            sprite_chars(1, c), transparent_char(0x00), attr(0) {};
    SpriteComponent(std::string filename);
    int width;
    int height;
    std::vector<int> sprite_chars;
    int transparent_char;
    int attr;
};

class KeyboardControlledMovementComponent : public BaseComponent<KeyboardControlledMovementComponent>
{
public:
    KeyboardControlledMovementComponent(int mag) : magnitude(mag) {};

    int magnitude;
};

class WidgetComponent : public BaseComponent<WidgetComponent>
{
public:
    WidgetComponent(std::unique_ptr<Swears::Widget>& static_widget, std::unique_ptr<Swears::Widget>& widget) :
            static_widget(std::move(static_widget)), child(std::move(widget))
    {
        this->child->SetParent(this->static_widget.get());
    };

    std::unique_ptr<Swears::Widget> static_widget;
    std::unique_ptr<Swears::Widget> child;

};

class CellValueComponent : public BaseComponent<CellValueComponent>
{
public:

    CellValueComponent(void) : value(0) {};
    CellValueComponent(int val) : value(val) {};

    int value;
};

class CellTypeComponent : public BaseComponent<CellTypeComponent>
{
public:
    enum class CellType
    {
        Starting,
        Locked,
        Free
    };
    CellTypeComponent(CellType t) : cell_type(t) {};

    CellType cell_type;
};

class StateComponent : public BaseComponent<StateComponent>
{
public:
    StateComponent(void) : selected_row(0), selected_col(0) {};
    int selected_col;
    int selected_row;
};

class CellPosComponent : public BaseComponent<CellPosComponent>
{
public:
    CellPosComponent(int x, int y) : x(x), y(y) {};
    int x, y;
};

#endif // _GAME_COMPONENTS_HPP_