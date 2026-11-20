//
// Created by Dmitri on 2026-11-19.
//

#ifndef MAGNET_SIMULATOR_SUPPORT_H
#define MAGNET_SIMULATOR_SUPPORT_H
#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

#include "../MathUtil.h"

#include <glm/geometric.hpp>
#include <glm/vec2.hpp>

inline glm::vec2 GetFurthestPoint(const std::vector<Vertex>& vertices, glm::vec2 direction) {

    glm::vec2 max = vertices[0].position;
    float distMax = glm::dot(direction, max);

    for (const Vertex& vertex : vertices) {
        float dst = glm::dot(vertex.position, direction);

        if (dst > distMax) {
            distMax = dst;
            max = vertex.position;
        }
    }

    return max;
}

inline bool SameDirection(glm::vec2 direction, glm::vec2 AO) {
    return glm::dot(direction, AO) > 0.0f;
}

inline glm::vec2 Support(const std::vector<Vertex>& vertices, glm::vec2 direction) {
    return GetFurthestPoint(vertices, direction);
}

#endif //MAGNET_SIMULATOR_SUPPORT_H
