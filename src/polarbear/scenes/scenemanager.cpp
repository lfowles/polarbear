#include <polarbear/scenes/scenemanager.hpp>

void SceneManager::SetScene(ScenePtr scene)
{
    if (stack.size() > 0) {
        stack.back()->Destroy();
        stack.pop_back();
    }
    stack.push_back(scene);
    stack.back()->Init();
}

void SceneManager::PushScene(ScenePtr scene)
{
    if (stack.size() > 0)
    {
        stack.back()->Pause();
    }
    stack.push_back(scene);
    stack.back()->Init();
}

void SceneManager::PopScene(void)
{
    stack.back()->Destroy();
    stack.pop_back();
    if (stack.size() > 0)
    {
        stack.back()->Resume();
    }
}

void SceneManager::Update(ms elapsed)
{
    if (stack.size() > 0)
    {
        stack.back()->Update(elapsed);
    }
}