//
// Created by Dmitri on 2026-11-16.
//

#include "DipoleModel.h"

void DipoleModel::Populate(Magnet &magnet, glm::vec2 dipole) {
    dipoles.push_back(dipole);
    magnets.push_back(magnet);
}

void DipoleModel::Step(float deltaTime) {

}
