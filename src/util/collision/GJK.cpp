//
// Created by Dmitri on 2026-11-19.
//

#include "GJK.h"

#include <iostream>
#include <ostream>

#include "Support.h"



bool GJK::SimplexLine(Simplex &simplex, glm::vec2& direction) {
    glm::vec2 A = simplex[0];
    glm::vec2 B = simplex[1];

    glm::vec2 AB = B - A;
    glm::vec2 AO = -A;

    if (SameDirection(AB, AO)) {
        direction = glm::dot(glm::vec2(-AB.y, AB.x), AO) > 0.0f
            ? glm::vec2(-AB.y, AB.x)
            : glm::vec2(AB.y, -AB.x);
    }
    else {
        simplex = { A };
        direction = AO;
    }

    return false;
}

bool GJK::SimplexTriangle(Simplex &simplex, glm::vec2& direction) {
    glm::vec2 A = simplex[0];
    glm::vec2 B = simplex[1];
    glm::vec2 C = simplex[2];

    glm::vec2 AB = B - A;
    glm::vec2 AC = C - A;
    glm::vec2 AO = -A;

    glm::vec2 ABperp(-AB.y, AB.x);
    glm::vec2 ACperp(AC.y, -AC.x);

    if (glm::dot(ABperp, AC) > 0.0f)
        ABperp = -ABperp;

    if (glm::dot(ACperp, AB) > 0.0f)
        ACperp = -ACperp;

    if (SameDirection(ABperp, AO)) {
        simplex = { A, B };
        direction = ABperp;
        return false;
    }

    if (SameDirection(ACperp, AO)) {
        simplex = { A, C };
        direction = ACperp;
        return false;
    }

    return true;
}

bool GJK::HandleSimplex(Simplex &simplex, glm::vec2& direction) {
    switch (simplex.Size()) {
        case 2: return SimplexLine(simplex, direction);
        case 3: return SimplexTriangle(simplex, direction);
    }

    return false;
}

Collision GJK::PerformGJK(const std::vector<Vertex>& A, const std::vector<Vertex>& B) {

    Collision collision{};
    collision.collided = false;

    glm::vec2 support = Support(A, glm::vec2(1.0f, 0.0f)) - Support(B, glm::vec2(-1.0f, 0.0f));

    Simplex simplex;
    simplex.PushFront(support);

    glm::vec2 direction = -support;

    for (int i = 0; i < 100; i++) {
        glm::vec2 va = Support(A, direction);
        glm::vec2 vb = Support(B, -direction);

        support = va - vb;

        if (glm::dot(support, direction) <= 0.0f)
            return collision;

        simplex.PushFront(support);

        if (HandleSimplex(simplex, direction)) {
            collision = EPA::PerformEPA(simplex, A, B);
            return collision;
        }
    }

    return collision;
}


