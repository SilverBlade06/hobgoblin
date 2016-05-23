#include "vertices.h"

GLuint generateVBO(GLuint vbo, GLsizeiptr size, const GLvoid * data) {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    return vbo;
}

GLuint generateVAO(GLuint vao, GLuint vbo, GLuint verticesPerDraw) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Vertices
    glVertexAttribPointer(0, verticesPerDraw, GL_FLOAT, GL_FALSE, 5 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    // Texture coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
            (GLvoid*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Cleanup
    glBindVertexArray(0);
    return vao;
}
