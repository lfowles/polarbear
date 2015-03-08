#ifndef _POLARBEAR_SCENES_MAINMENU_HPP_
#define _POLARBEAR_SCENES_MAINMENU_HPP_

#include "../config.hpp"
#include "../systems/systemmanager.hpp"
#include "../events/event.hpp"
#include "scene.hpp"

class MainMenuScene : public Scene
{

public:
    MainMenuScene(EventDispatch& dispatch) : dispatch(&dispatch) {};

    virtual void Init(void) override;

    virtual void Pause(void) override{};

    virtual void Resume(void) override {};

    virtual void Update(ms elapsed) override;

    virtual void Destroy(void) override {};
private:
    SystemManager systems;
    EventDispatch* dispatch;
};

#endif // _POLARBEAR_SCENES_MAINMENU_HPP_
