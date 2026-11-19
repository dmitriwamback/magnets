#include <iostream>

#include "src/scene/Renderer.h"

int main() {

    Renderer renderer = Renderer();
    renderer.Initialize();
    renderer.GameLoop();
}
