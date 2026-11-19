//
// Created by Dmitri on 2026-11-16.
//

#include "Camera.h"

#include <iostream>
#include <ostream>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::ComputeProjectionMatrix(float width, float height) {
    return glm::perspective(3.14159265358f/2.0f, width/height, 0.1f, 1000.0f);
}

glm::mat4 Camera::ComputeViewMatrix() {
    return glm::lookAt(glm::vec3(position, 10.0f), glm::vec3(position, 5.0f) + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0, 1, 0));
}