//
// Created by Dmitri on 2026-11-16.
//

#include "DipoleModel.h"

#include <iostream>
#include <ostream>

void DipoleModel::Populate(Magnet &magnet, glm::dvec2 dipole, double strength) {
    auto d = Dipole(dipole, strength);
    dipoles.emplace_back(d);
    magnets.push_back(magnet);
}

void DipoleModel::Step(float deltaTime) {

    const size_t n = magnets.size();
    std::vector<glm::dvec2> forces(n, glm::dvec2(0));
    std::vector<double> torques(n, 0.0);

    for (size_t i = 0; i < n; i++) {
        const glm::dvec2 mI = dipoles[i].GetDipole() * dipoles[i].Strength();
        glm::dvec2 netField(0);

        for (size_t j = 0; j < n; j++) {
            if (i == j) continue;

            const glm::dvec2 mJ = dipoles[j].GetDipole() * dipoles[j].Strength();
            const glm::dvec2 r = magnets[i].position - magnets[j].position;
            if (glm::length(r) >= R) continue;

            double d;
            const glm::dvec2 r_hat = soften(r, d);

            netField  += w(r) * B(r_hat, mJ, d);
            forces[i] += calculateForce(mJ, mI, r_hat, r, d);
        }
        torques[i] = torque(netField, mI);
    }

    double dt = static_cast<double>(deltaTime);

    for (size_t i = 0; i < n; i++) {
        const double w_ = magnets[i].scale.x, h_ = magnets[i].scale.y;
        const double inertia = magnets[i].mass * (w_ * w_ + h_ * h_) / 12.0;

        magnets[i].angularVelocity += (torques[i] / inertia) * dt;
        magnets[i].angularVelocity *= 1.0 - angularDrag * dt;
        const double dTheta = magnets[i].angularVelocity * dt;
        magnets[i].rotation += dTheta;
        dipoles[i].Rotate(dTheta);

        magnets[i].velocity += (forces[i] / magnets[i].mass) * dt;
        magnets[i].velocity *= 1.0 - linearDrag * dt;
        magnets[i].position += magnets[i].velocity * dt;
    }
}

void DipoleModel::Render(Shader& shader, float deltaTime) {
    for (int i = 0; i < magnets.size(); i++) {
        Magnet& magnet = magnets[i];
        Dipole dipole = dipoles[i];

        glm::mat4 model = ComputeModelMatrix(glm::vec3(magnet.position, 0.0f), glm::vec3(0.0f, 0.0f, magnet.rotation), glm::vec3(magnet.scale, 1.0f));
        shader.SetMatrix4("model", model);
        shader.SetVector2("magnetCenter", magnet.position);
        shader.SetFloat("momentAngle", (float)dipole.TotalAngle());
        magnet.Render(deltaTime);
    }
}