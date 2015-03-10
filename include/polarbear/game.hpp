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
    void do_scenechange(void);
    void handle_quit(EventPtr& event);
    void handle_scenechange(EventPtr& event);
    std::vector<EventPtr> scene_changes;
};

#endif // _POLARBEAR_GAME_HPP_
