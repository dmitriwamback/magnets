//
// Created by Dmitri on 2026-11-19.
//

#ifndef MAGNET_SIMULATOR_SIMPLEX_H
#define MAGNET_SIMULATOR_SIMPLEX_H
#include <array>
#include <glm/vec2.hpp>

class Simplex {
public:
    Simplex() : simplexSize(0) {}

    Simplex& operator=(std::initializer_list<glm::vec2> list);
    glm::vec2& operator[](unsigned int i);

    void PushFront(glm::vec2 point);
    unsigned Size();

    std::array<glm::vec2, 3>::iterator Begin();
    std::array<glm::vec2, 3>::iterator End();

private:
    std::array<glm::vec2, 3> points;
    int simplexSize;
};


#endif //MAGNET_SIMULATOR_SIMPLEX_H
