//
// Created by Dmitri on 2026-11-16.
//

#ifndef MAGNET_SIMULATOR_DIPOLEMODEL_H
#define MAGNET_SIMULATOR_DIPOLEMODEL_H
#include <glm/vec2.hpp>

#include "Dipole.h"
#include "../Model.h"


class DipoleModel: public Model {
public:
    DipoleModel() = default;

    void Populate(Magnet& magnet, glm::dvec2 dipole, double strength);
    void Step(float deltaTime) override;
private:

    double linearDrag  = 2.0;
    double angularDrag = 5.0;
    std::vector<Dipole> dipoles;
};


#endif //MAGNET_SIMULATOR_DIPOLEMODEL_H
