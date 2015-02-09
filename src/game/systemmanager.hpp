#ifndef _GAME_SYSTEMMANAGER_HPP_
#define _GAME_SYSTEMMANAGER_HPP_

#include <memory>
#include <vector>
#include "systems.hpp"
#include "entity.hpp"
#include "helpers.hpp"

class SystemManager
{
public:
    SystemManager(void) = default;
    SystemManager(double max_update_rate) : ms_per_update(1000.0/max_update_rate), accumulated_time(0.0) {};
    void AddSystem(std::shared_ptr<System>& system)
    {
        systems.push_back(std::move(system));
    };

    void AddSystem(std::shared_ptr<System>&& system)
    {
        systems.push_back(std::move(system));
    };

    void AddSystem(System*&& system)
    {
        systems.push_back(std::shared_ptr<System>(system));
    }

    void AddEntity(Entity& entity)
    {
        entities.push_back(std::move(entity));
    };

    void update(ms time_elapsed)
    {
        accumulated_time += time_elapsed;
        while (accumulated_time > ms_per_update)
        {
            for (auto &system : systems)
            {
                system->update(entities, ms_per_update);
                accumulated_time -= ms_per_update;
            }
        }
    };

    void SetMaxUpdateRate(double max_update_rate) { ms_per_update = ms(1.0/max_update_rate); };
private:
    std::vector<std::shared_ptr<System>> systems;
    std::vector<Entity> entities;
    ms ms_per_update;
    ms accumulated_time;
};


#endif // _GAME_SYSTEMMANAGER_HPP_