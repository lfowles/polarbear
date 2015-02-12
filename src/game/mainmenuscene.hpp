#ifndef _GAME_MAINMENUSCENE_HPP_
#define _GAME_MAINMENUSCENE_HPP_

#include "config.hpp"
#include "scene.hpp"

class MainMenuScene : public Scene
{

public:
    MainMenuScene(EventDispatch& dispatch) : dispatch(&dispatch) {};

    virtual void Init(void)
    {
        systems.SetMaxUpdateRate(UPDATE_HZ);
        auto rendering_system = new CursesRenderSystem(dispatch, RENDER_HZ);
        systems.AddSystem(std::unique_ptr<System>(rendering_system));

        auto input_system = new CursesInputSystem(dispatch, rendering_system->Stdscr());
        //systems.AddSystem(std::unique_ptr<System>(input_system));
        systems.AddSystem(input_system);

        Entity a, b, c;
        auto d = std::unique_ptr<Component>(new DrawableComponent ('[', 1, 1));
        a.AddComponent(d);
        systems.AddEntity(a);

        auto e = std::unique_ptr<Component>(new DrawableComponent('J', 1+19*2, 20));
        b.AddComponent(e);
        systems.AddEntity(b);

        auto f = std::unique_ptr<Component>(new DrawableComponent('N', 2, 1));
        c.AddComponent(f);
        systems.AddEntity(c);


    };

    virtual void Pause(void) {};

    virtual void Resume(void) {};

    virtual void Update(ms elapsed) {systems.update(elapsed);};

    virtual void Destroy(void) {};
private:
    SystemManager systems;
    EventDispatch* dispatch;
};

#endif // _GAME_MAINMENUSCENE_HPP_
