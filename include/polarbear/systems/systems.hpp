#ifndef _GAME_SYSTEMS_HPP_
#define _GAME_SYSTEMS_HPP_

#include <bitset>
#include <iostream>
#include <memory>
#include <vector>
#include "../entity.hpp"
#include "../event.hpp"
#include <swears/curses.hpp>
#include <swears/input.hpp>
#include "../cursessingleton.hpp"



#include <polarbear/helpers.hpp>

//class Event;
//using EventPtr = std::shared_ptr<Event>;

class System
{
public:
    System(EventDispatch* dispatch) : dispatch(dispatch) {};
    virtual ~System(void) {};
    virtual void update(std::vector<Entity>& entities, ms time_elapsed) = 0;
    virtual void handle(EventPtr& event) {};
protected:
    EventDispatch* dispatch;
};

class CursesRenderSystem : public System
{
public:
    CursesRenderSystem(EventDispatch* dispatch, double max_render_rate) :
            System(dispatch), ms_per_render(1000.0/max_render_rate), accumulated_time(0.0),
            curses(CursesSingleton::GetCurses())
    {
        // This should rather be set up at the beginning of the game
        curses->raw(true);
        curses->echo(false);
        curses->refresh();
        curses->Cursor(Swears::Curses::Visibility::Invisible);
    }

    virtual void update(std::vector<Entity>& entities, ms time_elapsed)
    {
        accumulated_time += time_elapsed;
        if (accumulated_time > ms_per_render)
        {
            render(entities, ms_per_render);
            accumulated_time = ms(0.0);// -= ms_per_render;
        }
    }

    void render(std::vector<Entity>& entities, ms time_elapsed)
    {
        curses->stdscr.Clear();

        // Draw gui in here? Loop over all widgets and call Draw I guess

        std::vector<std::pair<SpriteComponent*, PositionComponent*>> to_draw;
        for (auto& entity : entities)
        {
            auto pos = entity.Get<PositionComponent>();
            if (pos == nullptr)
            {
                continue;
            }

            auto sprite = entity.Get<SpriteComponent>();
            if (sprite != nullptr)
            {
                to_draw.push_back({sprite, pos});
            }

            auto widget = entity.Get<WidgetComponent>();
            if (widget != nullptr)
            {
                auto size = entity.Get<SizeComponent>();
                if (size != nullptr)
                {
                    auto size_vec = Swears::Vec2{size->x, size->y};
                    auto origin = Swears::Vec2{pos->x, pos->y};
                    widget->child->Draw(origin, size_vec, curses->stdscr);
                }
            }
        }

        std::cout << to_draw.size() << std::endl;
        std::sort(to_draw.begin(), to_draw.end(),
                [](std::pair<SpriteComponent*, PositionComponent*> a, std::pair<SpriteComponent*, PositionComponent*> b)
                {
                    //std::cout << b.second << " " << a.second << std::endl;
                    return a.second->z < b.second->z;
                }
        );

        auto size = curses->stdscr.Size();
        for (auto& sprite_pair : to_draw)
        {
            auto& sprite = sprite_pair.first;
            auto& pos = sprite_pair.second;
            if (sprite->attr)
            {
                curses->stdscr.AttrOn(sprite->attr);
            }

            for (int y = 0; y < sprite->height and y + pos->y <= size.y; y++) {
                for (int x = 0; x < sprite->width and x + pos->x <= size.x; x++) {
                    auto &c = sprite->sprite_chars[y * sprite->width + x];
                    if (c != sprite->transparent_char) {
                        curses->stdscr.Write(c & 0xff, {pos->x + x, pos->y + y});
                    }
                }
            }
            if (sprite->attr)
            {
                curses->stdscr.AttrOff(sprite->attr);
            }
        }
        curses->refresh();
    }

private:
    CursesPtr curses;
    ms ms_per_render;
    ms accumulated_time;
};

class CursesInputSystem : public System
{
public:
    CursesInputSystem(EventDispatch* dispatch, Swears::Window& window) :
            System(dispatch), input(window) {};

    virtual void update(std::vector<Entity> &entities, ms time_elapsed)
    {
        while (input.has_input())
        {
            auto event = EventPtr(new InputEvent(input.read()));
            dispatch->QueueEvent(event);
        }
    };

private:
    Swears::Input input;
};

class KeyboardControllerSystem : public System
{
public:
    KeyboardControllerSystem(EventDispatch* dispatch) :
            System(dispatch)
    {
        EventDelegate delegate = std::bind(&KeyboardControllerSystem::HandleInput, this, std::placeholders::_1);
        dispatch->Register(EventType::Input, delegate);
        accumulators.resize(2);
    };

    void HandleInput(EventPtr& event)
    {
        auto input_event = std::dynamic_pointer_cast<InputEvent>(event);

        if (input_event->key < 128 and input_event->key >= 0)
        {
            accumulators[1].set(input_event->key);
        }
    }

    virtual void update(std::vector<Entity> &entities, ms time_elapsed)
    {
        for (auto& entity : entities)
        {
            auto keyboard_movement = entity.Get<KeyboardControlledMovementComponent>();
            if (keyboard_movement == nullptr)
            {
                continue;
            }

            auto pos = entity.Get<PositionComponent>();
            if (pos == nullptr)
            {
                continue;
            }

            // This should really generate movement events that get immediately dispatched using SendEvent!
            // This way AI and players can have MovableComponents that receive Move events
            auto magnitude = keyboard_movement->magnitude;//*time_elapsed.count()/1000;

            if (accumulators[1].test('w'))
            {
                pos->y -= magnitude;
            }

            if (accumulators[1].test('a'))
            {
                pos->x -= magnitude;
            }

            if (accumulators[1].test('s'))
            {
                pos->y += magnitude;
            }

            if (accumulators[1].test('d'))
            {
                pos->x += magnitude;
            }

        }

        // Move new accumulator to old accumulator spot
        if (accumulators[0].any() or accumulators[1].any())
        {
            accumulators.emplace_back();
            accumulators.erase(accumulators.begin());
        }
    }

    // 0 is the old accumulator, 1 is the new accumulator
    std::vector<std::bitset<128>> accumulators;


};

class SudokuLogicSystem : public System
{
public:
    SudokuLogicSystem(EventDispatch* dispatch) :
        System(dispatch), selected_row(0), selected_col(0), entered_value(0), entering_value(false)
    {
        EventDelegate delegate = std::bind(&SudokuLogicSystem::HandleInput, this, std::placeholders::_1);
        dispatch->Register(EventType::Input, delegate);
    };

    void HandleInput(EventPtr& event)
    {
        auto input_event = std::dynamic_pointer_cast<InputEvent>(event);

        if (input_event->key == KEY_ENTER or input_event->key == 0x0A or input_event->key == 0x0D )
        {
            entering_value = not entering_value;
            return;
        }

        if (not entering_value)
        {
            if (input_event->key >= 'a' and input_event->key <= 'i') {
                selected_row = input_event->key-'a';
            } else if (input_event->key >= '1' and input_event->key <= '9') {
                selected_col = input_event->key-'1';
            } else if (input_event->key == KEY_LEFT) {
                selected_col = (selected_col+8) % 9; // +8, because % is more of a remainder than modulo
            } else if (input_event->key == KEY_RIGHT) {
                selected_col = (selected_col+1) % 9;
            } else if (input_event->key == KEY_UP) {
                selected_row = (selected_row+8) % 9; // +8, because % is more of a remainder than modulo
            } else if (input_event->key == KEY_DOWN) {
                selected_row = (selected_row+1) % 9;
            }

        } else {
            if (input_event->key >= '1' and input_event->key <= '9')
            {
                entered_value = input_event->key - '1';
            }
        }
    }
    virtual void update(std::vector<Entity> &entities, ms time_elapsed)
    {
        for (auto& entity : entities)
        {
            auto cell_type = entity.Get<CellTypeComponent>();
            if (cell_type == nullptr)
            {
                continue;
            }

            auto cell_value = entity.Get<CellValueComponent>();
            if (cell_value == nullptr)
            {
                continue;
            }

            auto pos = entity.Get<CellPosComponent>();
            if (pos == nullptr)
            {
                continue;
            }

            auto sprite = entity.Get<SpriteComponent>();
            if (sprite == nullptr)
            {
                continue;
            }

            if (cell_type->cell_type == CellTypeComponent::CellType::Locked)
            {
                sprite->attr = A_BOLD;
            } else if (cell_type->cell_type == CellTypeComponent::CellType::Free and pos->x == selected_col and pos->y == selected_row) {
                sprite->attr = A_UNDERLINE | A_BOLD;
            } else {
                sprite->attr = 0;
            }

            if (pos->x == selected_col and pos->y == selected_row)
            {
                if (entering_value)
                {
                    cell_value->value = entered_value;
                } else {
                    entered_value = cell_value->value;
                }
            }

            if (cell_value->value == 0)
            {
                sprite->sprite_chars[0] = '_';
            } else {
                sprite->sprite_chars[0] = '0'+cell_value->value;
            }
        }
    }

    int selected_row;
    int selected_col;
    bool entering_value;
    int entered_value;

};

class GameEngineSystem : public System
{

};

#endif // _GAME_SYSTEMS_HPP_


