#ifndef _GAME_ENTITY_HPP_
#define _GAME_ENTITY_HPP_

#include <vector>

class Component
{
    void update(double time_elapsed);
};

class Entity
{
    std::vector<Component> components;
};

#endif // _GAME_ENTITY_HPP_