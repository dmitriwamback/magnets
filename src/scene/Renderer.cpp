//
// Created by Dmitri on 2026-11-16.
//

#include "Renderer.h"

#include <iostream>
#include <sstream>

#include "../util/MathUtil.h"

void Renderer::Initialize() {

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return;
    }

#if defined(__APPLE__)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    window = glfwCreateWindow(1200, 800, "Magnet Simulation", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, CursorPositionCallback);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();


    if (err != GLEW_OK) {
        std::cerr << "GLEW init failed: " << glewGetErrorString(err) << std::endl;
    }
    glEnable(GL_DEPTH_TEST);

    // test
    double d;
    glm::dvec2 r = glm::dvec2(5, 1); // direction between two magnets
    glm::dvec2 r_hat = soften(r, d); // normalized with epsilon

    std::cout << "r_hat: (" << r_hat.x << ", " << r_hat.y << ") - d: " << d <<  std::endl;

    glm::dvec2 dipole = glm::dvec2(0, 1);
    glm::dvec2 field = B(r_hat, dipole, d);

    std::cout << "field: (" << field.x << ", " << field.y << ")" << std::endl;
}

void Renderer::GameLoop() {

    while (!glfwWindowShouldClose(window)) {

        double currentTime = glfwGetTime();
        deltaTime = float(currentTime - lastFrameTime);
        lastFrameTime = currentTime;

        frameCount++;
        if (currentTime - fpsTimer >= 1.0) {
            std::stringstream ss;
            ss << "Magnet Simulation - FPS: " << frameCount;
            glfwSetWindowTitle(window, ss.str().c_str());
            frameCount = 0;
            fpsTimer += 1.0;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

void Renderer::CursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {

    auto* self = static_cast<Renderer*>(glfwGetWindowUserPointer(window));

    if (glfwGetMouseButton(window, self->camera.mouseButton)) {
        float dy = ypos - self->camera.lastMouseY;
        float dx = xpos - self->camera.lastMouseX;

        self->camera.position += glm::vec2(dx, dy);
    }

    self->camera.lastMouseX = xpos;
    self->camera.lastMouseY = ypos;
}