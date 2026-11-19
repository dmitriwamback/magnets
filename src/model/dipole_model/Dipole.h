//
// Created by Dmitri on 2026-11-19.
//

#ifndef MAGNET_SIMULATOR_DIPOLE_H
#define MAGNET_SIMULATOR_DIPOLE_H
#include <glm/vec2.hpp>


class Dipole {
public:
    Dipole(glm::dvec2 dipole, double strength);
    glm::dvec2 GetDipole();
    double Angle();
    double Strength();
    void Rotate(double angle);
private:
    glm::dvec2 dipole;
    double initialAngle, currentAngle = 0;
    double strength;
};


#endif //MAGNET_SIMULATOR_DIPOLE_H
