#include <polarbear/systems/systems.hpp>

void System::entity_added(std::shared_ptr <Entity> &entity)
{
    if (system_mask.any() and (entity->component_mask & system_mask) == system_mask)
    {
        interesting_entities.push_back(entity);
    }
}
