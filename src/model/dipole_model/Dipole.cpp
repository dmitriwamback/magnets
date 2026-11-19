//
// Created by Dmitri on 2026-11-19.
//

#include "Dipole.h"

#include <glm/trigonometric.hpp>

Dipole::Dipole(glm::dvec2 dipole) {
    this->dipole = dipole;
    initialAngle = glm::atan(dipole.y, dipole.x);
}

double Dipole::Angle() {
    return initialAngle;
}

glm::dvec2 Dipole::GetDipole() {
    return dipole;
}
