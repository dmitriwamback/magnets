cmake_minimum_required(VERSION 4.3)
project(magnet_simulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(magnet_simulator main.cpp
        src/scene/Renderer.cpp
        src/scene/Renderer.h
        src/scene/Scene.cpp
        src/scene/Scene.h
        src/scene/Camera.cpp
        src/scene/Camera.h
        src/WorldSettings.h
        src/model/dipole_model/DipoleModel.cpp
        src/model/dipole_model/DipoleModel.h
        src/model/two_pole_model/TwoPoleModel.cpp
        src/model/two_pole_model/TwoPoleModel.h
        src/util/QuadTree.cpp
        src/util/QuadTree.h
        src/model/Model.cpp
        src/model/Model.h
        src/object/Magnet.cpp
        src/object/Magnet.h
        src/shader/Shader.cpp
        src/shader/Shader.h
        src/shader/ShaderSources.h
        src/util/MathUtil.h
        src/model/dipole_model/Dipole.cpp
        src/model/dipole_model/Dipole.h)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

target_link_libraries(magnet_simulator PRIVATE
    glfw
    GLEW::GLEW
    glm::glm
)
