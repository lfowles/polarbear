#include <polarbear/scenes/scenemanager.hpp>

void SceneManager::SetScene(ScenePtr scene)
{
    if (not stack.empty())
    {
        stack.back()->Destroy();
        stack.pop_back();
    }
    stack.push_back(scene);
    stack.back()->Init();
}

void SceneManager::PushScene(ScenePtr scene)
{
    if (not stack.empty())
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
    if (not stack.empty())
    {
        stack.back()->Resume();
    }
}

void SceneManager::Update(ms elapsed)
{
    // All states in the stack will update, it's up to the states to make sure that when they transition they set their systems to something reasonable
    for (auto& scene : stack)
    {
        scene->Update(elapsed);
    }
}