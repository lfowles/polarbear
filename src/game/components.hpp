#ifndef _GAME_COMPONENTS_HPP_
#define _GAME_COMPONENTS_HPP_

// instead of a scene graph, have components like "AttachedTo(parent)", etc

enum class ComponentType
{
    None,
    Drawable,
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

class DrawableComponent : public Component
{
public:
    DrawableComponent(char c, int x, int y) : Component(ComponentType::Drawable), c(c), x(x), y(y) {};

    char c;
    int x, y;
};

class SpriteComponent : public Component
{
public:
    std::vector<std::vector<int>> sprite;
    int transparent;
};

#endif // _GAME_COMPONENTS_HPP_