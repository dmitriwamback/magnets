//
// Created by Dmitri on 2026-11-16.
//

#include "DipoleModel.h"

void DipoleModel::Populate(Magnet &magnet, glm::dvec2 dipole) {
    auto d = Dipole(dipole);
    dipoles.emplace_back(d);
    magnets.push_back(magnet);
}

void DipoleModel::Step(float deltaTime) {

}
