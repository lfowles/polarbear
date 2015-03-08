#ifndef _POLARBEAR_COMPONENTS_SUDOKUCOMPONENTS_HPP_
#define _POLARBEAR_COMPONENTS_SUDOKUCOMPONENTS_HPP_

#include "components.hpp"

class CellValueComponent : public BaseComponent<CellValueComponent>
{
public:

    CellValueComponent(void) : value(0) {};
    CellValueComponent(int val) : value(val) {};

    int value;
};

class CellTypeComponent : public BaseComponent<CellTypeComponent>
{
public:
    enum class CellType
    {
        Starting,
        Locked,
        Free
    };
    CellTypeComponent(CellType t) : cell_type(t) {};

    CellType cell_type;
};

class StateComponent : public BaseComponent<StateComponent>
{
public:
    StateComponent(void) : selected_row(0), selected_col(0) {};
    int selected_col;
    int selected_row;
};

class CellPosComponent : public BaseComponent<CellPosComponent>
{
public:
    CellPosComponent(int x, int y) : x(x), y(y) {};
    int x, y;
};

#endif // _POLARBEAR_COMPONENTS_SUDOKUCOMPONENTS_HPP_