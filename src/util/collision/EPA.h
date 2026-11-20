
//
// Created by Dmitri on 2026-11-19.
//

#ifndef MAGNET_SIMULATOR_EPA_H
#define MAGNET_SIMULATOR_EPA_H

#include <vector>
#include <utility>
#include <glm/vec2.hpp>

#include "Simplex.h"
#include "../MathUtil.h"

struct Collision {
    bool collided = false;
    glm::vec2 normal = glm::vec2(0.0f);
    float depth = 0.0f;
};

class EPA {
public:
    static std::pair<glm::vec2, float> GetNormal(const std::vector<glm::vec2>& polytope, size_t index);
    static Collision PerformEPA(Simplex& simplex, const std::vector<Vertex>& A, const std::vector<Vertex>& B);
};

#endif // MAGNET_SIMULATOR_EPA_H
