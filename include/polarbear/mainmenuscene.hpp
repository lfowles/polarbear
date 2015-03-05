#ifndef _GAME_MAINMENUSCENE_HPP_
#define _GAME_MAINMENUSCENE_HPP_

#include "config.hpp"
#include "scene.hpp"
#include "cursessingleton.hpp"
#include <swears/widgets/staticwidget.hpp>
#include <swears/widgets/fillwidget.hpp>

class MainMenuScene : public Scene
{

public:
    MainMenuScene(EventDispatch& dispatch) : dispatch(&dispatch) {};

    virtual void Init(void)
    {
        auto curses = CursesSingleton::GetCurses();
        systems.SetMaxUpdateRate(UPDATE_HZ);
        auto rendering_system = new CursesRenderSystem(dispatch, RENDER_HZ);

        systems.AddSystem(rendering_system);

        auto input_system = new CursesInputSystem(dispatch, curses->stdscr);
        systems.AddSystem(input_system);

        auto keyboard_system = new KeyboardControllerSystem(dispatch);
        systems.AddSystem(keyboard_system);

        Entity a, b, c, widget;
        {
            auto pos = std::unique_ptr<Component>(new PositionComponent(0, 0, 1));
            auto sprite = std::unique_ptr<Component>(new SpriteComponent(RESOURCE_PATH "test.sprite"));
            auto movement = std::unique_ptr<Component>(new KeyboardControlledMovementComponent(1));
            a.AddComponent(pos);
            a.AddComponent(sprite);
            a.AddComponent(movement);
        }

        {
            auto pos = std::unique_ptr<Component>(new PositionComponent(1 + 19 * 2, 20));
            auto sprite = std::unique_ptr<Component>(new SpriteComponent(2,2,{'a','b','c','d'},0x00));

            b.AddComponent(pos);
            b.AddComponent(sprite);
        }

        {
            auto pos = std::unique_ptr<Component>(new PositionComponent(2, 1));
            auto sprite = std::unique_ptr<Component>(new SpriteComponent(2,2,{'d','a','c','d'},0x00));

            c.AddComponent(pos);
            c.AddComponent(sprite);
        }

        {
            auto base_widget = std::unique_ptr<Swears::Widget>(new Swears::StaticWidget(curses->stdscr.Size()));
            auto fill_widget = std::unique_ptr<Swears::Widget>(new Swears::FillWidget(Swears::Vec2{3,10},'x'));

            auto pos = std::unique_ptr<Component>(new PositionComponent(10, 10));
            auto size = std::unique_ptr<Component>(new SizeComponent(3, 10));

            auto widget_component = std::unique_ptr<Component>(new WidgetComponent(base_widget, fill_widget));
            widget.AddComponent(widget_component);
            widget.AddComponent(pos);
            widget.AddComponent(size);
        }

        systems.AddEntity(widget);
        systems.AddEntity(a);
        systems.AddEntity(b);
        systems.AddEntity(c);
    };

    virtual void Pause(void) {};

    virtual void Resume(void) {};

    virtual void Update(ms elapsed)
    {
        systems.update(elapsed);
    };

    virtual void Destroy(void) {};
private:
    SystemManager systems;
    EventDispatch* dispatch;
};

#endif // _GAME_MAINMENUSCENE_HPP_
