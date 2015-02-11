#ifndef _GAME_MAINMENUSCENE_HPP_
#define _GAME_MAINMENUSCENE_HPP_

#include "scene.hpp"

class MainMenuScene : public Scene
{

public:
    virtual void Init(void)
    {

    };

    virtual void Pause(void) {};

    virtual void Resume(void) {};

    virtual void Update(ms elapsed) {};

    virtual void Destroy(void) {};
private:
};

#endif // _GAME_MAINMENUSCENE_HPP_
