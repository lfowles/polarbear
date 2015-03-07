#ifndef _GAME_ENTITY_HPP_
#define _GAME_ENTITY_HPP_

#include "components.hpp"

#include <algorithm>
#include <bitset>
#include <memory>
#include <vector>

class Entity
{
public:
    template <typename T>
    void AddComponent(std::unique_ptr<T>& component)
    {
        components.push_back(std::move(component));
        component_mask.set(T::type);
    }

    template <typename T>
    void RemoveComponent(void)
    {
        auto component_iter = std::find_if(components.begin(), components.end(),
                [](const std::unique_ptr<Component> &component)
                {
                    return component->Type() == T::type;
                }
        );

        if (component_iter != components.end())
        {
            components.erase(component_iter);
        }
        component_mask.reset(T::type);
    }

    template <typename T>
    void ReplaceComponent(std::unique_ptr<T>& component)
    {
        auto component_iter = std::find_if(components.begin(), components.end(),
                [](const std::unique_ptr<Component> &component)
                {
                    return component->Type() == T::type;
                }
        );

        if (component_iter == components.end())
        {
            AddComponent(component);
        } else {
            components[component_iter] = component;
        }
    }

    template <typename T>
    T* Get()
    {
        auto component_iter = std::find_if(components.begin(), components.end(),
                [](const std::unique_ptr<Component> &component)
                {
                    return component->Type() == T::type;
                }
        );
        if (component_iter == components.end())
        {
            return nullptr;
        } else {
            return static_cast<T*>(component_iter->get());
        }
    }
    std::vector<std::unique_ptr<Component>> components;

    // FIXME: Determine # of components at compile time? Probably not, depends on templates being instantiated. Just make sure not to exceed N!
    std::bitset<max_components> component_mask;
};

#endif // _GAME_ENTITY_HPP_