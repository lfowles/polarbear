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

        //auto keyboard_system = new KeyboardControllerSystem(dispatch);
        //systems.AddSystem(keyboard_system);

        auto logic_system = new SudokuLogicSystem(dispatch);
        systems.AddSystem(logic_system);

//        Entity a, b, c, widget;
        {
            Entity a;
            auto pos = std::unique_ptr<Component>(new PositionComponent(0, 0, 1));
            auto sprite = std::unique_ptr<Component>(new SpriteComponent(RESOURCE_PATH "test.sprite"));
            auto movement = std::unique_ptr<Component>(new KeyboardControlledMovementComponent(1));
            a.AddComponent(pos);
            a.AddComponent(sprite);
            a.AddComponent(movement);
            systems.AddEntity(a);
        }
        {
            Entity board_highlights;
            auto pos = std::unique_ptr<Component>(new PositionComponent(0, 0, 2));
            auto spriteptr = new SpriteComponent(RESOURCE_PATH "test_overlay.sprite");
            spriteptr->attr = A_BOLD;
            auto sprite = std::unique_ptr<Component>(spriteptr);
            auto movement = std::unique_ptr<Component>(new KeyboardControlledMovementComponent(1));
            board_highlights.AddComponent(pos);
            board_highlights.AddComponent(sprite);
            board_highlights.AddComponent(movement);
            systems.AddEntity(board_highlights);
        }
        {
            Entity state;
            auto state_component = std::unique_ptr<Component>(new StateComponent());
            state.AddComponent(state_component);
            systems.AddEntity(state);
        }
        for (int r=0; r<9; r++)
        {
            auto y = r*2+2;

            for (int c=0; c<9; c++)
            {
                Entity cell;
                auto x = 4*c+4;
                auto pos = std::unique_ptr<Component>(new PositionComponent(x, y, 1));
                cell.AddComponent(pos);
                auto grid_pos = std::unique_ptr<Component>(new CellPosComponent(c, r));
                cell.AddComponent(grid_pos);
                auto cell_value = std::unique_ptr<Component>(new CellValueComponent(c));
                cell.AddComponent(cell_value);
                auto sprite = std::unique_ptr<Component>(new SpriteComponent(0x30+c));
                cell.AddComponent(sprite);
                auto cell_type = std::unique_ptr<Component>(new CellTypeComponent(CellTypeComponent::CellType::Free));
                cell.AddComponent(cell_type);
                systems.AddEntity(cell);
            }
        }



//        for(auto i=0; i<9; i++)
//        {
//            auto pos = std::unique_ptr<Component>(new PositionComponent(1 + 19 * 2, 20));
//            auto sprite = std::unique_ptr<Component>(new SpriteComponent(2,2,{'a','b','c','d'},0x00));
//
//            b.AddComponent(pos);
//            b.AddComponent(sprite);
//        }
//
//        {
//            auto pos = std::unique_ptr<Component>(new PositionComponent(2, 1));
//            auto sprite = std::unique_ptr<Component>(new SpriteComponent(2,2,{'d','a','c','d'},0x00));
//
//            c.AddComponent(pos);
//            c.AddComponent(sprite);
//        }
//
//        {
//            auto base_widget = std::unique_ptr<Swears::Widget>(new Swears::StaticWidget(curses->stdscr.Size()));
//            auto fill_widget = std::unique_ptr<Swears::Widget>(new Swears::FillWidget(Swears::Vec2{3,10},'x'));
//
//            auto pos = std::unique_ptr<Component>(new PositionComponent(10, 10));
//            auto size = std::unique_ptr<Component>(new SizeComponent(3, 10));
//
//            auto widget_component = std::unique_ptr<Component>(new WidgetComponent(base_widget, fill_widget));
//            widget.AddComponent(widget_component);
//            widget.AddComponent(pos);
//            widget.AddComponent(size);
//        }

//        systems.AddEntity(widget);

//        systems.AddEntity(b);
//        systems.AddEntity(c);
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
