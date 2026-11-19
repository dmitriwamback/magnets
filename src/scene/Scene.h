//
// Created by Dmitri on 2026-11-16.
//

#ifndef MAGNET_SIMULATOR_SCENE_H
#define MAGNET_SIMULATOR_SCENE_H
#include <vector>

#include "Camera.h"
#include "../model/Model.h"
#include "../object/Magnet.h"
#include "../shader/Shader.h"


class Scene {
public:
    void SetModel(ModelType model);
    void Populate(Magnet& magnet, glm::vec2 dipole);
    void Render(Camera& camera, float deltaTime);

private:
    Model* magneticModel;
    Shader shader;
};


#endif //MAGNET_SIMULATOR_SCENE_H
