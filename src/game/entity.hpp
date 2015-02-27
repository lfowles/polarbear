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

    Component* GetComponent(ComponentType type)
    {
        for (auto& component : components)
        {
            if (component->Type() == type)
            {
                return component.get();
            }
        }
        return nullptr;
    }
    std::vector<std::unique_ptr<Component>> components;
};

#endif // _GAME_ENTITY_HPP_