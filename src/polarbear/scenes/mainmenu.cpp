#include <polarbear/scenes/mainmenu.hpp>

#include <polarbear/components/sudokucomponents.hpp>
#include <polarbear/systems/cursesrender.hpp>
#include <polarbear/systems/cursesinput.hpp>
#include <polarbear/systems/sudokulogic.hpp>

void MainMenuScene::Init(void)
{
    auto logic_system = new SudokuLogicSystem(dispatch);
    systems.AddSystem(logic_system);

    auto curses = CursesSingleton::GetCurses();
    systems.SetUpdateTime(update_duration);
    auto rendering_system = new CursesRenderSystem(dispatch, render_duration);

    systems.AddSystem(rendering_system);

    auto input_system = new CursesInputSystem(dispatch, curses->stdscr);
    systems.AddSystem(input_system);

    {
        Entity a;
        auto pos = std::unique_ptr<PositionComponent>(new PositionComponent(0, 0, 1));
        auto sprite = std::unique_ptr<SpriteComponent>(new SpriteComponent(RESOURCE_PATH "test.sprite"));
        auto movement = std::unique_ptr<KeyboardControlledMovementComponent>(new KeyboardControlledMovementComponent(1));
        a.AddComponent(pos);
        a.AddComponent(sprite);
        a.AddComponent(movement);
        systems.AddEntity(a);
    }
    {
        Entity board_highlights;
        auto pos = std::unique_ptr<PositionComponent>(new PositionComponent(0, 0, 2));
        auto sprite = std::unique_ptr<SpriteComponent>(new SpriteComponent(RESOURCE_PATH "test_overlay.sprite"));
        sprite->attr = A_BOLD;

        auto movement = std::unique_ptr<KeyboardControlledMovementComponent>(new KeyboardControlledMovementComponent(1));
        board_highlights.AddComponent(pos);
        board_highlights.AddComponent(sprite);
        board_highlights.AddComponent(movement);
        systems.AddEntity(board_highlights);
    }
    {
        Entity state;
        auto state_component = std::unique_ptr<StateComponent>(new StateComponent());
        state.AddComponent(state_component);
        systems.AddEntity(state);
    }

    for (int r = 0; r < 9; r++)
    {
        auto y = r * 2 + 2;

        for (int c = 0; c < 9; c++)
        {
            Entity cell;
            auto x = 4 * c + 4;
            auto pos = std::unique_ptr<PositionComponent>(new PositionComponent(x, y, 1));
            cell.AddComponent(pos);
            auto grid_pos = std::unique_ptr<CellPosComponent>(new CellPosComponent(c, r));
            cell.AddComponent(grid_pos);
            auto cell_value = std::unique_ptr<CellValueComponent>(new CellValueComponent(c));
            cell.AddComponent(cell_value);
            auto sprite = std::unique_ptr<SpriteComponent>(new SpriteComponent(0x30 + c));
            cell.AddComponent(sprite);
            auto cell_type = std::unique_ptr<CellTypeComponent>(new CellTypeComponent(CellTypeComponent::CellType::Free));
            cell.AddComponent(cell_type);
            systems.AddEntity(cell);
        }
    }
}

void MainMenuScene::Update(ms elapsed)
{
        systems.update(elapsed);
}