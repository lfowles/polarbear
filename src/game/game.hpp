#ifndef _GAME_GAME_HPP_
#define _GAME_GAME_HPP_

constexpr int UPDATE_HZ = 60;
constexpr int RENDER_HZ = 30;
constexpr int MAXIMUM_HZ = 100;

#include <queue>

#include "entity.hpp"
#include "event.hpp"
#include "systemmanager.hpp"
#include "systems.hpp"

class SuspendedMagic
{
public:
    void Run(void);
    void Init(void);
private:
    bool running;
    std::vector<Entity> entities;
    SystemManager systems;
    EventDispatch dispatch;
    std::shared_ptr<GameEngineSystem> engine_system;
    void handle_quit(EventPtr& event);
};

#endif // _GAME_GAME_HPP_