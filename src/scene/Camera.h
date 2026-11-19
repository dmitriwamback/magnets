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
    glm::vec2 position;
    float lastMouseX, lastMouseY;
    int mouseButton = GLFW_MOUSE_BUTTON_RIGHT;

private:
    glm::mat4 projection;
    glm::mat4 view;
};


#endif //MAGNET_SIMULATOR_CAMERA_H
