#ifndef _POLARBEAR_SCENES_SCENEMANAGER_HPP_
#define _POLARBEAR_SCENES_SCENEMANAGER_HPP_

#include <vector>

#include "scene.hpp"

class SceneManager
{
public:
    void SetScene(ScenePtr scene);
    void PushScene(ScenePtr scene);
    void PopScene(void);
    void Update(ms elapsed);

private:
    std::vector<ScenePtr> stack;
};

#endif // _POLARBEAR_SCENES_SCENEMANAGER_HPP_

