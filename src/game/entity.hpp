#ifndef _GAME_ENTITY_HPP_
#define _GAME_ENTITY_HPP_

#include "components.hpp"

#include <memory>
#include <vector>

class Entity
{
public:
    void AddComponent(std::unique_ptr<Component>& component)
    {
        components.push_back(std::move(component));
    }
    std::vector<std::unique_ptr<Component>> components;
};

#endif // _GAME_ENTITY_HPP_