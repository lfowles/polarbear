#include <polarbear/systems/sudokulogic.hpp>

#include <polarbear/components/components.hpp>
#include <polarbear/components/sudokucomponents.hpp>

SudokuBoard::SudokuBoard(void)
{
    cells.fill(0);
}

// Value can be 0-9
void SudokuBoard::set(int row, int col, int value)
{
    cells[row*9+col] = value;
}

int& SudokuBoard::get(int row, int col)
{
    return cells[row*9+col];
}

bool SudokuBoard::valid(int row, int col)
{
    // Can immediately return invalid if sum of row, column, or square is not 45
    // This is annoying and clutters up the code though :) I'm not sure how much faster it would be as a first pass

    auto value = get(row, col);

    if (value == 0)
    {
        return false;
    }

    // Duplicate number check
    for (auto r=0; r < 9; r++)
    {
        if (get(r, col) == value and r != row)
        {
            return false;
        }
    }

    for (auto c=0; c < 9; c++)
    {
        if (get(row, c) == value and c != col)
        {
            return false;
        }
    }

    auto box_col = col/3;
    auto box_row = row/3;

    for (auto r=0; r<3; r++)
    {
        auto actual_row = box_row*3+r;
        for (auto c=0; c<3; c++)
        {
            auto actual_col = box_col*3+r;
            if (get(actual_row, actual_col) == value and not (actual_row == row and actual_col == col))
            {
                return false;
            }
        }
    }

    return true;
}

bool SudokuBoard::solved(void)
{
    // There is probably a shortcut,
    // maybe something like one sample from every row, every column, and every square would work?

    for (auto cell : cells)
    {
        // Not solved if it's not filled out
        if (cell == 0)
        {
            return false;
        }
    }

    for (auto i=0; i<9; i++)
    {
        if (not valid(i, 0))
        {
            return false;
        }
        if (not valid(0, i))
        {
            return false;
        }
    }
    for (auto box_row=0; box_row<3; box_row++)
    {
        for (auto box_col=0; box_col<3; box_col++)
        {
            if (not valid(box_row*3, box_col*3))
            {
                return false;
            }
        }
    }

    return true;
}


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
        if (input_event->key >= '0' and input_event->key <= '9')
        {
            entered_value = input_event->key - '0';
        }
    }
}

void SudokuLogicSystem::update(ms time_elapsed)
{
    // Populate board
    for (auto& entity : interesting_entities)
    {
        auto cell_value = entity->Get<CellValueComponent>();
        auto pos = entity->Get<CellPosComponent>();
        board.set(pos->y, pos->x, cell_value->value);
    }

    for (auto& entity : interesting_entities)
    {
        auto cell_type = entity->Get<CellTypeComponent>();
        auto cell_value = entity->Get<CellValueComponent>();
        auto pos = entity->Get<CellPosComponent>();
        auto sprite = entity->Get<SpriteComponent>();

//        if (cell_type->cell_type == CellTypeComponent::CellType::Locked)
//        {
//            sprite->attr = A_BOLD;
//        } else if (cell_type->cell_type == CellTypeComponent::CellType::Free and pos->x == selected_col and pos->y == selected_row) {
//            sprite->attr = A_UNDERLINE | A_BOLD;
//        } else {
//            sprite->attr = 0;
//        }

        if (pos->x == selected_col and pos->y == selected_row)
        {
            if (entering_value)
            {
                cell_value->value = entered_value;
                board.set(pos->y, pos->x, cell_value->value);
            } else {
                entered_value = cell_value->value;
            }
        }

        if (not board.valid(pos->y, pos->x))
        {
            sprite->attr = A_REVERSE;
        } else {
            sprite->attr = 0;
        }

        if (cell_value->value == 0)
        {
            sprite->sprite_chars[0] = '_';
        } else {
            sprite->sprite_chars[0] = '0'+cell_value->value;
        }
    }
}
