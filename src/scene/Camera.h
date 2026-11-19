//
// Created by Dmitri on 2026-11-16.
//

#ifndef MAGNET_SIMULATOR_CAMERA_H
#define MAGNET_SIMULATOR_CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

class Camera {
public:
    glm::vec2 position = glm::vec2(0.0f);
    float lastMouseX, lastMouseY;
    int mouseButton = GLFW_MOUSE_BUTTON_LEFT;

    glm::mat4 ComputeProjectionMatrix(float width, float height);
    glm::mat4 ComputeViewMatrix();
};


#endif //MAGNET_SIMULATOR_CAMERA_H
