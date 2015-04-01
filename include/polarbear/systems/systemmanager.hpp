#ifndef _POLARBEAR_SYSTEMS_SYSTEMMANAGER_HPP_
#define _POLARBEAR_SYSTEMS_SYSTEMMANAGER_HPP_

#include <memory>
#include <vector>
#include "systems.hpp"
#include "../entity.hpp"
#include "../helpers.hpp"
#include "../config.hpp"

class SystemManager
{
public:
    SystemManager(void) : ms_per_update(update_duration), accumulated_time(0.0) {};
    void AddSystem(std::shared_ptr<System>& system);
    void AddSystem(std::shared_ptr<System>&& system);
    void AddSystem(System*&& system);
    void AddEntity(Entity& entity);
    void update(ms time_elapsed);
    void SetUpdateTime(s update_time);
    std::vector<std::shared_ptr<Entity>> GetEntities(std::bitset<max_components> mask);

    std::vector<std::shared_ptr<Entity>> entities;

private:
    std::vector<std::shared_ptr<System>> systems;
    ms ms_per_update;
    ms accumulated_time;
};


#endif // _POLARBEAR_SYSTEMS_SYSTEMMANAGER_HPP_