//
// Created by Dmitri on 2026-11-19.
//

#include "Simplex.h"

Simplex& Simplex::operator=(std::initializer_list<glm::vec2> list) {
    simplexSize = 0;

    for (const auto& point : list)
        points[simplexSize++] = point;

    return *this;
}

glm::vec2& Simplex::operator[](unsigned int i) {
    return points[i];
}

void Simplex::PushFront(glm::vec2 point) {
    if (simplexSize < 3)
        simplexSize++;

    for (int i = simplexSize - 1; i > 0; i--)
        points[i] = points[i - 1];

    points[0] = point;
}

unsigned Simplex::Size() {
    return simplexSize;
}

std::array<glm::vec2, 3>::iterator Simplex::Begin() {
    return points.begin();
}

std::array<glm::vec2, 3>::iterator Simplex::End() {
    return points.begin() + simplexSize;
}
