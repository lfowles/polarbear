#include <polarbear/systems/systemmanager.hpp>

void SystemManager::AddSystem(std::shared_ptr<System>& system)
{
    systems.push_back(std::move(system));
};

void SystemManager::AddSystem(std::shared_ptr<System>&& system)
{
    systems.push_back(std::move(system));
};

void SystemManager::AddSystem(System*&& system)
{
    systems.push_back(std::shared_ptr<System>(system));
}

void SystemManager::AddEntity(Entity& entity)
{
    entities.push_back(std::move(entity));
};

void SystemManager::update(ms time_elapsed)
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

void SystemManager::SetMaxUpdateRate(double max_update_rate)
{
    ms_per_update = ms(1.0/max_update_rate);
};