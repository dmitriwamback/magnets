//
// Created by Dmitri on 2026-11-18.
//

#ifndef MAGNET_SIMULATOR_SHADERSOURCES_H
#define MAGNET_SIMULATOR_SHADERSOURCES_H

inline const char* DEFAULT_VERTEX_SHADER_SOURCE = R"(
#version 410 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out prop {
    vec2 uv;
    vec2 fragp;
} vs_out;

void main() {
    vs_out.uv = uv;
    vs_out.fragp = position;

    gl_Position = projection * view * model * vec4(position, 0.0, 1.0);
}
)";


inline const char* DEFAULT_FRAGMENT_SHADER_SOURCE = R"(
#version 410 core

out vec4 fragc;

in prop {
    vec2 uv;
    vec2 fragp;
} fs_in;

void main() {
    fragc = vec4(1.0);
}
)";

#endif //MAGNET_SIMULATOR_SHADERSOURCES_H
