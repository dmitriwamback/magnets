//
// Created by Dmitri on 2026-11-16.
//

#ifndef MAGNET_SIMULATOR_RENDERER_H
#define MAGNET_SIMULATOR_RENDERER_H

#include "Scene.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderer {
public:
    void Initialize();
    void GameLoop();
private:
    Scene scene;
    Camera camera;
    GLFWwindow* window;
};


#endif //MAGNET_SIMULATOR_RENDERER_H
