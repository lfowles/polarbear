#ifndef _POLARBEAR_GAME_HPP_
#define _POLARBEAR_GAME_HPP_

#include "events/event.hpp"
#include "events/eventdispatch.hpp"
#include "scenes/scenemanager.hpp"

class Polarbear
{
public:
    Polarbear(void);
    void Run(void);
    virtual void Init(void) = 0;

protected:
    SceneManager scenemanager;
    EventDispatch dispatch;

private:
    bool running;
    void handle_quit(EventPtr& event);
};

#endif // _POLARBEAR_GAME_HPP_
