#include <polarbear/systems/sudokulogic.hpp>

#include <polarbear/components/components.hpp>
#include <polarbear/components/sudokucomponents.hpp>

SudokuLogicSystem::SudokuLogicSystem(EventDispatch * dispatch) :
        System(dispatch), selected_row(0), selected_col(0), entered_value(0), entering_value(false)
{
    EventDelegate delegate = std::bind(&SudokuLogicSystem::HandleInput, this, std::placeholders::_1);
    dispatch->Register(EventType::Input, delegate);

    system_mask.set(CellPosComponent::type);
    system_mask.set(CellTypeComponent::type);
    system_mask.set(CellValueComponent::type);
    system_mask.set(SpriteComponent::type);
}

void SudokuLogicSystem::HandleInput(EventPtr & event)
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

void SudokuLogicSystem::update(ms time_elapsed)
{
    for (auto& entity : interesting_entities)
    {
        auto cell_type = entity->Get<CellTypeComponent>();
        auto cell_value = entity->Get<CellValueComponent>();
        auto pos = entity->Get<CellPosComponent>();
        auto sprite = entity->Get<SpriteComponent>();

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
