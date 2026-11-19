//
// Created by Dmitri on 2026-11-16.
//

#include "Scene.h"

#include "../model/dipole_model/DipoleModel.h"
#include "../model/two_pole_model/TwoPoleModel.h"
#include "../shader/ShaderSources.h"

Scene::Scene() {
}

void Scene::SetModel(ModelType modelType) {

    shader = Shader(DEFAULT_VERTEX_SHADER_SOURCE, DEFAULT_FRAGMENT_SHADER_SOURCE);
    switch (modelType) {
        case ModelType::DIPOLE_MODEL:
            magneticModel = new DipoleModel();
            break;
        case ModelType::TWO_POLE_MODEL:
            magneticModel = new TwoPoleModel();
            break;
    }
}

void Scene::Populate(Magnet& magnet, double strength = 0.0, glm::dvec2 dipole = glm::dvec2(0.0)) {

    if (DipoleModel* dipoleModel = dynamic_cast<DipoleModel*>(magneticModel)) {
        if (glm::length(dipole) < 0.00001) {
            throw std::runtime_error("Dipole model needs a dipole");
        }
        dipoleModel->Populate(magnet, dipole, strength);
    }
    else if (TwoPoleModel* twoPoleModel = dynamic_cast<TwoPoleModel*>(magneticModel)) {
        //twoPoleModel->Populate(magnet);
    }
}

void Scene::Render(Camera& camera, float deltaTime, float width, float height) {

    shader.Use();
    magneticModel->Step(deltaTime);

    glm::mat4 projection = camera.ComputeProjectionMatrix(width, height);
    glm::mat4 view = camera.ComputeViewMatrix();

    shader.SetMatrix4("projection", projection);
    shader.SetMatrix4("view", view);

    magneticModel->Render(shader, deltaTime);
}
