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
    // This is good enough for now, with a mostly static list of entities and components, but in the future this will need some sort of hook on AddComponent/RemoveComponent
    entities.push_back(std::make_shared<Entity>(std::move(entity)));

    for (auto &system : systems)
    {
        if (system->system_mask.any() and (entities.back()->component_mask & system->system_mask) == system->system_mask)
        {
            system->interesting_entities.push_back(entities.back());
        }
    }
};

void SystemManager::update(ms time_elapsed)
{
    accumulated_time += time_elapsed;
    while (accumulated_time > ms_per_update)
    {
        for (auto &system : systems)
        {
            system->update(ms_per_update);
            accumulated_time -= ms_per_update;
        }
    }
};

void SystemManager::SetUpdateTime(s update_time)
{
    ms_per_update = ms(update_time);
};