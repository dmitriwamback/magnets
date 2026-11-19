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

void Scene::Populate(Magnet& magnet) {
    magneticModel->Populate(magnet);
}

void Scene::Render(Camera& camera) {

}
