#ifndef _POLARBEAR_SYSTEMS_SYSTEMS_HPP_
#define _POLARBEAR_SYSTEMS_SYSTEMS_HPP_

#include <memory>
#include <vector>

#include "../entity.hpp"
#include "../events/eventdispatch.hpp"
#include "../helpers.hpp"

class SystemManager;
class System
{
public:
    System(EventDispatch* dispatch, SystemManager* systems) : dispatch(dispatch), systems(systems)
    {
        IDDispenser dispenser{};
        dispatch_id = dispenser.dispense();
    };
    virtual ~System(void) {};
    virtual void update(ms time_elapsed) = 0;
    virtual void handle(EventPtr& event) {};
    virtual void entity_added(std::shared_ptr<Entity>& entity);
    std::bitset<max_components> system_mask;
    std::vector<std::shared_ptr<Entity>> interesting_entities;
protected:
    EventDispatch* dispatch;
    SystemManager* systems;
    OriginID dispatch_id;

};

#endif // _POLARBEAR_SYSTEMS_SYSTEMS_HPP_


