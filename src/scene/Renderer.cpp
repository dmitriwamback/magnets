//
// Created by Dmitri on 2026-11-16.
//

#include "Renderer.h"

#include <iostream>
#include <sstream>
#include <random>

#include "../util/MathUtil.h"

Renderer::Renderer() {}

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

    camera = Camera();

    scene = Scene();
    scene.SetModel(ModelType::DIPOLE_MODEL);

    DipoleModelSceneSetup();
}

void Renderer::GameLoop() {

    bool spacePressed = false;
    bool resetScene = false;

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

        if (!spacePressed && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            scene.SetPaused(!scene.IsPaused());
            spacePressed = true;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
            spacePressed = false;
        }

        if (!resetScene && glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            scene.Clear();
            DipoleModelSceneSetup();
            resetScene = true;
        }
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE) {
            resetScene = false;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        scene.Render(camera, deltaTime, (float)width, (float)height);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

void Renderer::CursorPositionCallback(GLFWwindow *window, double xpos, double ypos) {

    auto* self = static_cast<Renderer*>(glfwGetWindowUserPointer(window));

    if (glfwGetMouseButton(window, self->camera.mouseButton)) {
        float dy = ypos - self->camera.lastMouseY;
        float dx = xpos - self->camera.lastMouseX;

        self->camera.position -= glm::vec2(dx, -dy) * 0.025f;
    }

    self->camera.lastMouseX = xpos;
    self->camera.lastMouseY = ypos;
}

void Renderer::DipoleModelSceneSetup() {
    double magnetStrength = 25000.0;
    int s = 7;

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> angle(0.0, 2.0 * M_PI);

    for (int x = 0; x < s; x++) {
        for (int y = 0; y < s; y++) {
            double a = angle(rng);
            glm::dvec2 moment(cos(a), sin(a));

            Magnet magnet;
            magnet.position = glm::dvec2(x - s / 2, y - s / 2) * 4.0;
            scene.Populate(magnet, magnetStrength, moment);
        }
    }
}
