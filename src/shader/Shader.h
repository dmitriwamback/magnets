//
// Created by Dmitri on 2026-11-18.
//

#ifndef MAGNET_SIMULATOR_SHADER_H
#define MAGNET_SIMULATOR_SHADER_H


#include <glm/ext/matrix_float4x4.hpp>
#include <cstdint>

class Shader {
public:
    Shader();
    Shader(const char* vertexShaderSource, const char* fragmentShaderSource);
    void Use();
    void SetMatrix4(const char* variableName, const glm::mat4& matrix);
    void SetVector3(const char* variableName, const glm::vec3& vector);
    void SetVector2(const char* variableName, const glm::vec2& vector);
    void SetInt(const char *variableName, int value);

private:
    uint32_t program;
    int LoadShaderSource(const char* source, int type);
};


#endif //MAGNET_SIMULATOR_SHADER_H
