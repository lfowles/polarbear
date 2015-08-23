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

    // TODO : Manually add entities to systems, this seems to be the clearest way to signal intent. Ex: create entity but don't "enable" it yet
    // This requires I get past using unique_ptr for everything, since systemmanager just took ownership :
    // TODO: Go to the whole arrays of components thing.
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
