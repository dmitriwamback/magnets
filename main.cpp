#include <iostream>

#include "src/scene/Renderer.h"

int main() {
    Renderer renderer;
    renderer.Initialize();
    renderer.GameLoop();
}
