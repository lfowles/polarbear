#ifndef _POLARBEAR_SYSTEMS_KEYBOARDCONTROLLER_HPP_
#define _POLARBEAR_SYSTEMS_KEYBOARDCONTROLLER_HPP_

#include "systems.hpp"

class KeyboardControllerSystem : public System
{
public:
    KeyboardControllerSystem(EventDispatch* dispatch);
    void HandleInput(EventPtr& event);
    virtual void update(ms time_elapsed) override;

    // 0 is the old accumulator, 1 is the new accumulator
    std::vector<std::bitset<128>> accumulators;

};

#endif // _POLARBEAR_SYSTEMS_KEYBOARDCONTROLLER_HPP_