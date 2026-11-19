//
// Created by Dmitri on 2026-11-16.
//

#include "Scene.h"

#include "../model/dipole_model/DipoleModel.h"
#include "../model/two_pole_model/TwoPoleModel.h"

void Scene::SetModel(ModelType modelType) {
    switch (modelType) {
        case ModelType::DIPOLE_MODEL:
            magneticModel = new DipoleModel();
            break;
        case ModelType::TWO_POLE_MODEL:
            magneticModel = new TwoPoleModel();
            break;
    }
}

void Scene::Populate(Magnet& magnet, glm::vec2 dipole = glm::vec2(0.0f)) {

    if (DipoleModel* dipoleModel = dynamic_cast<DipoleModel*>(magneticModel)) {
        if (glm::length(dipole) < 0.00001) {
            throw std::runtime_error("Dipole model needs a dipole");
        }
        dipoleModel->Populate(magnet, dipole);
    }
    else if (TwoPoleModel* twoPoleModel = dynamic_cast<TwoPoleModel*>(magneticModel)) {
        //twoPoleModel->Populate(magnet);
    }
}

void Scene::Render(Camera& , float deltaTime) {
    magneticModel->Step(deltaTime);
    magneticModel->Render();
}
