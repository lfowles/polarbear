#ifndef _POLARBEAR_SCENES_SCENE_HPP_
#define _POLARBEAR_SCENES_SCENE_HPP_

#include <memory>

#include "../helpers.hpp"
#include "../events/eventdispatch.hpp"

// Holds entitymanager, systemmanager, etc
class Scene
{
public:
    virtual ~Scene()
    {
        IDDispenser dispenser{};
        dispatch_id = dispenser.dispense();
    };
    virtual void Init(void) {};
    virtual void Pause(void) {};
    virtual void Resume(void) {};
    virtual void Update(ms elapsed) {};
    virtual void Destroy(void) {};
protected:
    OriginID dispatch_id;
};

using ScenePtr = std::shared_ptr<Scene>;

#endif // _POLARBEAR_SCENES_SCENE_HPP_
