#ifndef _GAME_GAME_HPP_
#define _GAME_GAME_HPP_


#include <queue>

#include "entity.hpp"
#include "event.hpp"
#include "systems/systemmanager.hpp"
#include "systems/systems.hpp"
#include "scene.hpp"

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

#endif // _GAME_GAME_HPP_
