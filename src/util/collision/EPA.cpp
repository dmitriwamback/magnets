
//
// Created by Dmitri on 2026-11-19.
//

#include "EPA.h"

#include <cfloat>
#include <cmath>
#include <glm/glm.hpp>
#include <algorithm>

#include "Support.h"

std::pair<glm::vec2, float> EPA::GetNormal(const std::vector<glm::vec2>& polytope, size_t index) {

    glm::vec2 A = polytope[index];
    glm::vec2 B = polytope[(index + 1) % polytope.size()];

    glm::vec2 edge = B - A;
    glm::vec2 normal(edge.y, -edge.x);

    float magnitude = glm::length(normal);

    if (magnitude < 0.000001f)
        return { glm::vec2(0.0f), FLT_MAX };

    normal /= magnitude;

    float dst = glm::dot(normal, A);

    if (dst < 0.0f) {
        normal = -normal;
        dst = -dst;
    }

    return { normal, dst };
}

Collision EPA::PerformEPA(Simplex& simplex, const std::vector<Vertex>& A, const std::vector<Vertex>& B) {

    Collision collision{};

    if (simplex.Size() != 3)
        return collision;

    std::vector<glm::vec2> polytope(simplex.Begin(), simplex.End());

    float area = 0.0f;

    for (size_t i = 0; i < polytope.size(); i++) {
        area += polytope[i].x * polytope[(i + 1) % polytope.size()].y
              - polytope[(i + 1) % polytope.size()].x * polytope[i].y;
    }

    if (area < 0.0f)
        std::reverse(polytope.begin(), polytope.end());

    glm::vec2 min(0.0f);
    float mindst = FLT_MAX;

    for (int k = 0; k < 100; k++) {

        size_t minEdge = 0;
        mindst = FLT_MAX;

        for (size_t i = 0; i < polytope.size(); i++) {

            auto [normal, dst] = GetNormal(polytope, i);

            if (dst < mindst) {
                mindst = dst;
                min = normal;
                minEdge = i;
            }
        }

        if (mindst == FLT_MAX)
            return collision;

        // Find the furthest point along the closest edge's normal.
        glm::vec2 support = Support(A, min) - Support(B, -min);

        float sdst = glm::dot(min, support);

        if (sdst - mindst < 0.001f) {
            collision.collided = true;
            collision.normal = min;
            collision.depth = std::min(mindst + 0.001f, 100.0f);

            return collision;
        }

        bool duplicate = false;

        for (const glm::vec2& point : polytope) {
            if (glm::length(point - support) < 1e-12f) {
                duplicate = true;
                break;
            }
        }

        if (duplicate)
            break;

        polytope.insert(polytope.begin() + minEdge + 1, support);
    }

    return collision;
}
