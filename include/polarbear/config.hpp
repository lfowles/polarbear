#ifndef _GAME_CONFIG_HPP_
#define _GAME_CONFIG_HPP_

#include "helpers.hpp"

// All in seconds, I need some way to represent this well in std::duration terms
constexpr int UPDATE_HZ = 60;
constexpr int RENDER_HZ = 30;
constexpr int MAXIMUM_HZ = 100;

constexpr s update_duration(1.0/UPDATE_HZ);
constexpr s render_duration(1.0/RENDER_HZ);
constexpr s min_loop_duration(1.0/MAXIMUM_HZ);

#endif // _GAME_CONFIG_HPP_
