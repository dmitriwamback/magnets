//
// Created by Dmitri on 2026-11-19.
//

#ifndef MAGNET_SIMULATOR_GJK_H
#define MAGNET_SIMULATOR_GJK_H
#include <glm/vec3.hpp>

#include "EPA.h"
#include "Simplex.h"
#include "../MathUtil.h"

class GJK {
public:
    static bool SimplexLine(Simplex& simplex, glm::vec2& direction);
    static bool SimplexTriangle(Simplex& simplex, glm::vec2& direction);
    static bool HandleSimplex(Simplex& simplex, glm::vec2& direction);

    static Collision PerformGJK(const std::vector<Vertex>& A, const std::vector<Vertex>& B);
};


#endif //MAGNET_SIMULATOR_GJK_H
