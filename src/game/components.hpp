#ifndef _GAME_COMPONENTS_HPP_
#define _GAME_COMPONENTS_HPP_

// instead of a scene graph, have components like "AttachedTo(parent)", etc

enum class ComponentType
{
    None,
    Position,
    Sprite,
    KeyboardControlledMovement,
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
    PositionComponent(float x, float y) : Component(ComponentType::Position), x(x), y(y) {};
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

#endif // _GAME_COMPONENTS_HPP_