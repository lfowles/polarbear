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
            sprite_chars(sprite), transparent_char(transparent) {};
    SpriteComponent(int c) :
            Component(ComponentType::Sprite), width(1), height(1),
            sprite_chars(1, c), transparent_char(0x00) {};
    SpriteComponent(std::string filename);
    int width;
    int height;
    std::vector<int> sprite_chars;
    int transparent_char;
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

#endif // _GAME_COMPONENTS_HPP_