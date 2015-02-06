#ifndef _GAME_ENTITY_HPP_
#define _GAME_ENTITY_HPP_

#include "components.hpp"

#include <vector>

class Entity
{
public:
    std::vector<Component*> components;
};

#endif // _GAME_ENTITY_HPP_