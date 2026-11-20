//
// Created by Dmitri on 2026-11-18.
//

#include "Magnet.h"

#include <iostream>
#include <GL/glew.h>

Magnet::Magnet() {

    vertices = {
        {{-1.0, -1.0}, {0.0, 0.0}},
        {{1.0, -1.0}, {1.0, 0.0}},
        {{1.0, 1.0}, {1.0, 1.0}},

        {{-1.0, -1.0}, {0.0, 0.0}},
        {{1.0, 1.0}, {1.0, 1.0}},
        {{-1.0, 1.0}, {0.0, 1.0}}
    };

    scale = glm::dvec2(0.65, 1.0);

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
}

void Magnet::Render(float deltaTime) {

    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

std::vector<Vertex> Magnet::GetTransformedVertices() {
    glm::mat4 model = ComputeModelMatrix(glm::vec3(position, 0.0f), glm::vec3(0.0f, 0.0f, rotation), glm::vec3(scale, 1.0f));
    std::vector<Vertex> _vertices;

    for (Vertex vertex : vertices) {
        glm::vec4 t = model * glm::vec4(vertex.position, 0.0f, 1.0f);
        _vertices.push_back({{t.x, t.y}, {0, 0}});
    }

    return _vertices;
}
