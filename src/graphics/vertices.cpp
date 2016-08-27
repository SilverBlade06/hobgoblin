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
    glVertexAttribPointer(0, verticesPerDraw, GL_FLOAT, GL_FALSE, 8 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    // Texture coords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
            (GLvoid*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Normal vectors
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
            (GLvoid*) (5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // Cleanup
    glBindVertexArray(0);
    return vao;
}

GLuint generateEBO(GLuint ebo, GLuint* indices) {
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    return ebo;
}

// Calculate normals
void calculateNormals(GLfloat *vertices, int size) {
    for (int i = 0; i < size; i++) {
        glm::vec3 vector1 = glm::vec3(
                vertices[i*24+0] - vertices[i*24+8],
                vertices[i*24+1] - vertices[i*24+9],
                vertices[i*24+2] - vertices[i*24+10]);
        glm::vec3 vector2 = glm::vec3(
                vertices[i*24+16] - vertices[i*24+8],
                vertices[i*24+17] - vertices[i*24+9],
                vertices[i*24+18] - vertices[i*24+10]);
        glm::vec3 normal = glm::normalize(glm::cross(vector2, vector1));
        vertices[i*24+5] = normal.x;
        vertices[i*24+6] = normal.y;
        vertices[i*24+7] = normal.z;
        vertices[i*24+13] = normal.x;
        vertices[i*24+14] = normal.y;
        vertices[i*24+15] = normal.z;
        vertices[i*24+21] = normal.x;
        vertices[i*24+22] = normal.y;
        vertices[i*24+23] = normal.z;
    }
}

void calculateNormals(GLfloat *vertices, int vertexSize, GLuint *indices, int indexSize) {
   glm::vec3 normalBeforeNormalized;
   for (int i = 0; i < indexSize; i++) {
       glm::vec3 vector1 = glm::vec3(
               vertices[indices[i*3]*8]   - vertices[indices[i*3+1]*8],
               vertices[indices[i*3]*8+1] - vertices[indices[i*3+1]*8+1],
               vertices[indices[i*3]*8+2] - vertices[indices[i*3+1]*8+2]);
       glm::vec3 vector2 = glm::vec3(
               vertices[indices[i*3+2]*8]   - vertices[indices[i*3+1]*8],
               vertices[indices[i*3+2]*8+1] - vertices[indices[i*3+1]*8+1],
               vertices[indices[i*3+2]*8+2] - vertices[indices[i*3+1]*8+2]);

       normalBeforeNormalized = glm::cross(vector2, vector1);
       vertices[indices[i*3]*8+5] += normalBeforeNormalized.x;
       vertices[indices[i*3]*8+6] += normalBeforeNormalized.y;
       vertices[indices[i*3]*8+7] += normalBeforeNormalized.z;
       vertices[indices[i*3+1]*8+5] += normalBeforeNormalized.x;
       vertices[indices[i*3+1]*8+6] += normalBeforeNormalized.y;
       vertices[indices[i*3+1]*8+7] += normalBeforeNormalized.z;
       vertices[indices[i*3+2]*8+5] += normalBeforeNormalized.x;
       vertices[indices[i*3+2]*8+6] += normalBeforeNormalized.y;
       vertices[indices[i*3+2]*8+7] += normalBeforeNormalized.z;
   }

   for (int i = 0; i < vertexSize; i++) {
       glm::vec3 normal = glm::normalize(glm::vec3(vertices[i*8+5], vertices[i*8+6], vertices[i*8+7]));
       vertices[i*8+5] = normal.x;
       vertices[i*8+6] = normal.y;
       vertices[i*8+7] = normal.z;
   }
}
