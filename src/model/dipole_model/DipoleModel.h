//
// Created by Dmitri on 2026-11-16.
//

#ifndef MAGNET_SIMULATOR_DIPOLEMODEL_H
#define MAGNET_SIMULATOR_DIPOLEMODEL_H
#include <glm/vec2.hpp>

#include "../Model.h"


class DipoleModel: public Model {
public:
    DipoleModel() = default;

    void Populate(Magnet& magnet, glm::vec2 dipole);
    void Step(float deltaTime) override;
private:
    std::vector<glm::vec2> dipoles;
};


#endif //MAGNET_SIMULATOR_DIPOLEMODEL_H
