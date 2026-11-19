//
// Created by Dmitri on 2026-11-19.
//

#include "Dipole.h"

#include <iostream>
#include <ostream>
#include <glm/trigonometric.hpp>

Dipole::Dipole(glm::dvec2 dipole, double strength) {
    this->dipole = dipole;
    this->strength = strength;

    initialAngle = glm::atan(dipole.y, dipole.x);
    currentAngle = 0;
}

double Dipole::Angle() {
    return initialAngle;
}

double Dipole::Strength() {
    return strength;
}

void Dipole::Rotate(double angle) {
    currentAngle += angle;
    dipole = glm::dvec2(cos(currentAngle + initialAngle), sin(currentAngle + initialAngle));
}

glm::dvec2 Dipole::GetDipole() {
    return dipole;
}
