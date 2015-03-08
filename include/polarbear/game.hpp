#ifndef _POLARBEAR_GAME_HPP_
#define _POLARBEAR_GAME_HPP_


#include <queue>

#include "entity.hpp"
#include "events/event.hpp"
#include "systems/systemmanager.hpp"
#include "systems/systems.hpp"
#include "scenes/scenemanager.hpp"

class SuspendedMagic
{
public:
    void Run(void);
    void Init(void);
private:
    bool running;
    EventDispatch dispatch;
    //std::shared_ptr<GameEngineSystem> engine_system;
    void handle_quit(EventPtr& event);
    SceneManager scenemanager;
};

#endif // _POLARBEAR_GAME_HPP_
