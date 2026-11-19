//
// Created by Dmitri on 2026-11-19.
//

#ifndef MAGNET_SIMULATOR_DIPOLE_H
#define MAGNET_SIMULATOR_DIPOLE_H
#include <glm/vec2.hpp>


class Dipole {
public:
    Dipole(glm::dvec2 dipole);
    glm::dvec2 GetDipole();
    double Angle();
private:
    glm::dvec2 dipole;
    double initialAngle;
};


#endif //MAGNET_SIMULATOR_DIPOLE_H
