#ifndef _GAME_GAME_HPP_
#define _GAME_GAME_HPP_

constexpr int UPDATE_HZ = 60;
constexpr int RENDER_HZ = 30;
constexpr int MAXIMUM_HZ = 100;

class SuspendedMagic
{
public:
    void run(void);
private:
    bool running;
};

#endif // _GAME_GAME_HPP_