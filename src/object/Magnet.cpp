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

    scale = glm::dvec2(0.5, 1.0);

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