#ifndef _GAME_ENTITY_HPP_
#define _GAME_ENTITY_HPP_

#include "components.hpp"

#include <vector>

class Entity
{
public:
    void AddComponent(Component&& component)
    {
        components.push_back(component);
    }
    std::vector<Component> components;
};

#endif // _GAME_ENTITY_HPP_