#ifndef _GAME_SCENE_HPP_
#define _GAME_SCENE_HPP_

#include <memory>

#include "helpers.hpp"
// Holds entitymanager, systemmanager, etc
class Scene
{
public:
    virtual ~Scene() {};
    virtual void Init(void) {};
    virtual void Pause(void) {};
    virtual void Resume(void) {};
    virtual void Update(ms elapsed) {};
    virtual void Destroy(void) {};
};

using ScenePtr = std::shared_ptr<Scene>;

class SceneManager
{
public:
    void SetScene(ScenePtr scene)
    {
        if (stack.size() > 0) {
            stack.back()->Destroy();
            stack.pop_back();
        }
        stack.push_back(scene);
        stack.back()->Init();
    };

    void PushScene(ScenePtr scene)
    {
        if (stack.size() > 0)
        {
            stack.back()->Pause();
        }
        stack.push_back(scene);
        stack.back()->Init();
    };

    void PopScene(void)
    {
        stack.back()->Destroy();
        stack.pop_back();
        if (stack.size() > 0)
        {
            stack.back()->Resume();
        }
    };

    void Update(ms elapsed)
    {
        if (stack.size() > 0)
        {
            stack.back()->Update(elapsed);
        }
    };
private:
    std::vector<ScenePtr> stack;
};

#endif // _GAME_SCENE_HPP_
