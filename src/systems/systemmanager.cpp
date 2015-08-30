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
    auto entity_ptr = std::make_shared<Entity>(std::move(entity));

    for (auto &system : systems)
    {
        system->entity_added(entity_ptr);
    }

    entities.push_back(entity_ptr);
};

void SystemManager::update(ms time_elapsed)
{
    accumulated_time += time_elapsed;
    while (accumulated_time > ms_per_update)
    {
        for (auto &system : systems)
        {
            system->update(ms_per_update);
        }
        accumulated_time -= ms_per_update;
    }
};

void SystemManager::SetUpdateTime(s update_time)
{
    ms_per_update = ms(update_time);
};

std::vector<std::shared_ptr<Entity>> SystemManager::GetEntities(std::bitset<max_components> mask)
{
    auto matching_entities = std::vector<std::shared_ptr<Entity>>{};
    for (auto& entity : entities)
    {
        if ((mask & entity->component_mask) == mask)
        {
            matching_entities.push_back(entity);
        }
    }
    return matching_entities;
}
