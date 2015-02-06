#ifndef _TUI_HELPERS_HPP_
#define _TUI_HELPERS_HPP_

#include <stdexcept>

namespace TUI
{
    class Vec2
    {
    public:
        Vec2() : Vec2(0,0) {};
        Vec2(int x, int y) : x(x), y(y) {};
        Vec2 operator+(const Vec2& other) { return Vec2(x + other.x, y + other.y); };
        Vec2 operator-(const Vec2& other) { return Vec2(x - other.x, y - other.y); };
        Vec2& operator+=(Vec2& other) { x += other.x; y += other.y; return *this; };
        Vec2& operator-=(Vec2& other) { x -= other.x; y -= other.y; return *this; };

        int x;
        int y;
    };

    class CursesError : public std::runtime_error
    {
    public:
        CursesError(const std::string& msg) : std::runtime_error::runtime_error(msg) {};
    };
}

#endif // _TUI_HELPERS_HPP_