#ifndef _GAME_COMPONENTS_HPP_
#define _GAME_COMPONENTS_HPP_

// instead of a scene graph, have components like "AttachedTo(parent)", etc

#include <string>
#include <vector>
#include <swears/widgets/widget.hpp>

enum class ComponentType
{
    None,
    Position,
    Sprite,
    KeyboardControlledMovement,
    Widget,
    Size,
    CellValue,
    CellType,
    CellPos,
    State,
    Fake
};

class Component
{
public:
    Component(void) : Component(ComponentType::Fake) {};
    Component(ComponentType type) : type(type) {};
    virtual ~Component() = default;
    virtual ComponentType Type(void) {return type;};
private:
    ComponentType type;
};

class PositionComponent : public Component
{
public:
    PositionComponent(float x, float y) : Component(ComponentType::Position), x(x), y(y), z(0.0f) {};
    PositionComponent(float x, float y, float z) : Component(ComponentType::Position), x(x), y(y), z(z) {};
    float x, y, z;
};

class SizeComponent : public Component
{
public:
    SizeComponent(float x, float y) : Component(ComponentType::Size), x(x), y(y) {};
    float x, y;
};


class SpriteComponent : public Component
{
public:
    SpriteComponent(int w, int h, const std::vector<int>& sprite, int transparent) :
            Component(ComponentType::Sprite), width(w), height(h),
            sprite_chars(sprite), transparent_char(transparent), attr(0) {};
    SpriteComponent(int c) :
            Component(ComponentType::Sprite), width(1), height(1),
            sprite_chars(1, c), transparent_char(0x00), attr(0) {};
    SpriteComponent(std::string filename);
    int width;
    int height;
    std::vector<int> sprite_chars;
    int transparent_char;
    int attr;
};

class KeyboardControlledMovementComponent : public Component
{
public:
    KeyboardControlledMovementComponent(int mag) :
            Component(ComponentType::KeyboardControlledMovement), magnitude(mag) {};

    int magnitude;
};

class WidgetComponent : public Component
{
public:
    WidgetComponent(std::unique_ptr<Swears::Widget>& static_widget, std::unique_ptr<Swears::Widget>& widget) :
            Component(ComponentType::Widget), static_widget(std::move(static_widget)), child(std::move(widget))
    {
        this->child->SetParent(this->static_widget.get());
    };

    std::unique_ptr<Swears::Widget> static_widget;
    std::unique_ptr<Swears::Widget> child;

};

class CellValueComponent : public Component
{
public:

    CellValueComponent(void) : Component(ComponentType::CellValue), value(0) {};
    CellValueComponent(int val) : Component(ComponentType::CellValue), value(val) {};

    int value;
};

class CellTypeComponent : public Component
{
public:
    enum class CellType
    {
        Starting,
        Locked,
        Free
    };
    CellTypeComponent(CellType t) : Component(ComponentType::CellType), cell_type(t) {};

    CellType cell_type;
};

class StateComponent : public Component
{
public:
    StateComponent(void) : Component(ComponentType::State), selected_row(0), selected_col(0) {};
    int selected_col;
    int selected_row;
};

class CellPosComponent : public Component
{
public:
    CellPosComponent(int x, int y) : Component(ComponentType::CellPos), x(x), y(y) {};
    int x, y;
};

#endif // _GAME_COMPONENTS_HPP_