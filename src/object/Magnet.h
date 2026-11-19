//
// Created by Dmitri on 2026-11-18.
//

#ifndef MAGNET_SIMULATOR_MAGNET_H
#define MAGNET_SIMULATOR_MAGNET_H

#include <stdint.h>
#include <vector>
#include <glm/vec2.hpp>

#include "../util/MathUtil.h"

class Magnet {
public:
    glm::dvec2 position, velocity, scale;
    double rotation, mass = 1.0, angularVelocity;
    Magnet();
    void Render(float deltaTime);

private:
    uint32_t vertexArrayObject, vertexBufferObject;
    std::vector<Vertex> vertices;
};


#endif //MAGNET_SIMULATOR_MAGNET_H
