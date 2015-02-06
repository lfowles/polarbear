#ifndef _GAME_SYSTEMMANAGER_HPP_
#define _GAME_SYSTEMMANAGER_HPP_

#include <vector>
#include "systems.hpp"
#include "entity.hpp"

class SystemManager
{
public:
    void AddSystem(System& system);
    void update(double time_elapsed)
    {
        for (auto& system : systems)
        {
            system.update(time_elapsed);
        }
    }
private:
    std::vector<System> systems;
    std::vector<Entity> entities;
};

#endif // _GAME_SYSTEMMANAGER_HPP_