//
// Created by Dmitri on 2026-11-16.
//

#ifndef MAGNET_SIMULATOR_RENDERER_H
#define MAGNET_SIMULATOR_RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.h"

class Renderer {
public:
    Renderer();
    void Initialize();
    void GameLoop();
private:
    Scene scene;
    Camera camera;
    GLFWwindow* window;

    float deltaTime;
    float lastFrameTime;
    int frameCount;
    int fpsTimer;

    static void CursorPositionCallback(GLFWwindow *window, double xpos, double ypos);
    void DipoleModelSceneSetup();
};


#endif //MAGNET_SIMULATOR_RENDERER_H
