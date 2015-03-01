#ifndef _GAME_SYSTEMMANAGER_HPP_
#define _GAME_SYSTEMMANAGER_HPP_

#include <memory>
#include <vector>
#include "systems.hpp"
#include "../entity.hpp"
#include "../helpers.hpp"

class SystemManager
{
public:
    SystemManager(void) = default;
    SystemManager(double max_update_rate) : ms_per_update(1000.0/max_update_rate), accumulated_time(0.0) {};
    void AddSystem(std::shared_ptr<System>& system);
    void AddSystem(std::shared_ptr<System>&& system);
    void AddSystem(System*&& system);
    void AddEntity(Entity& entity);
    void update(ms time_elapsed);
    void SetMaxUpdateRate(double max_update_rate);
private:
    std::vector<std::shared_ptr<System>> systems;
    std::vector<Entity> entities;
    ms ms_per_update;
    ms accumulated_time;
};


#endif // _GAME_SYSTEMMANAGER_HPP_