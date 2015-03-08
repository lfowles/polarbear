#ifndef _POLARBEAR_SYSTEMS_SUDOKULOGIC_HPP_
#define _POLARBEAR_SYSTEMS_SUDOKULOGIC_HPP_

#include "systems.hpp"

class SudokuLogicSystem : public System
{
public:
    SudokuLogicSystem(EventDispatch* dispatch);


    void HandleInput(EventPtr& event);

    virtual void update(ms time_elapsed) override;


    int selected_row;
    int selected_col;
    bool entering_value;
    int entered_value;

};

#endif // _POLARBEAR_SYSTEMS_SUDOKULOGIC_HPP_