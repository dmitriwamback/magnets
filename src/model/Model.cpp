//
// Created by Dmitri on 2026-11-16.
//

#include "Model.h"

void Model::Step(float deltaTime) {

}

void Model::Populate(Magnet &magnet) {
    magnets.push_back(magnet);
}

std::vector<Magnet> Model::Magnets() {
    return magnets;
}

void Model::Render(Shader& shader, float deltaTime) {
    for (Magnet &magnet : magnets) {
        glm::mat4 model = ComputeModelMatrix(glm::vec3(magnet.position, 0.0f), glm::vec3(0.0f, 0.0f, magnet.rotation), glm::vec3(magnet.scale, 1.0f));
        shader.SetMatrix4("model", model);
        magnet.Render(deltaTime);
    }
}
