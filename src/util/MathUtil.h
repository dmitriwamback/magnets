//
// Created by Dmitri on 2026-11-19.
//

#ifndef MAGNET_SIMULATOR_MATHUTIL_H
#define MAGNET_SIMULATOR_MATHUTIL_H

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

constexpr double MU_0 = 1.25663706e-6;
constexpr double k = MU_0 / (4.0 * M_PI);

#define R 40.0

struct Vertex {
    glm::vec2 position;
    glm::vec2 uv;
};

inline glm::mat4 ComputeModelMatrix(const glm::vec3 &position, const glm::vec3 &rotation, const glm::vec3 &size) {

    glm::mat4 translation = glm::translate(glm::mat4(1.0f), position);

    glm::mat4 xRotation = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 yRotation = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 zRotation = glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 rot = xRotation * yRotation * zRotation;
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), size);

    return translation * rot * scale;
}

inline glm::dvec2 soften(glm::dvec2 r, double& d) {
    double epsilon = 0.1;
    double len = glm::length(r);
    double d_squared = len*len + epsilon*epsilon;

    d = sqrt(d_squared);
    return r / sqrt(d_squared);
}

inline glm::dvec2 B(glm::dvec2 r, glm::dvec2 dipole, double d) {
    return k * (3.0 * glm::dot(dipole, r) * r - dipole)/pow(d, 3);
}

inline double w(glm::dvec2 r) {
    double s = glm::clamp((glm::length(r) - 0.8 * R)/(0.2 * R), 0.0, 1.0);
    return 1 - s * s * (3 - 2 * s);
}

inline double torque(glm::dvec2 B, glm::dvec2 dipole) {
    return dipole.x * B.y - dipole.y * B.x;
}

inline glm::dvec2 calculateForce(glm::dvec2 mJ, glm::dvec2 mI, glm::dvec2 r_hat, glm::dvec2 r, double d) {
    double coefficient = 3 * k * w(r) / pow(d, 4);

    double rj = glm::dot(mJ, r_hat),
           ri = glm::dot(mI, r_hat),
           ij = glm::dot(mI, mJ);

    return coefficient * (rj * mI + ri * mJ + ij * r_hat - 5 * rj * ri * r_hat);
}

#endif //MAGNET_SIMULATOR_MATHUTIL_H
