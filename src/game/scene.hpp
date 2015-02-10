#ifndef _GAME_SCENE_HPP_
#define _GAME_SCENE_HPP_

#include "helpers.hpp"
// Holds entitymanager, systemmanager, etc
class Scene
{
public:
    virtual void Init(void) {};
    virtual void Pause(void) {};
    virtual void Resume(void) {};
    virtual void Update(ms elapsed) {};

};

class SceneManager
{
public:
    void SetScene(Scene &scene)
    {
        if (stack.size() > 0) {
            stack[0] = scene;
        } else {
            stack.push_back(scene);
        }
    };

    void PushScene(Scene &scene)
    {
        stack.push_back(scene);
    };

    void PopScene(void)
    {
        stack.erase(stack.begin());
    };

    void Update(ms elapsed)
    {
        if (stack.size() > 0)
        {
            stack[0].Update(elapsed);
        }
    };
private:
    std::vector<Scene> stack;
};

#endif // _GAME_SCENE_HPP_