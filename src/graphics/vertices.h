#ifndef SRC_VERTICES_H_
#define SRC_VERTICES_H_

// Include GLEW (ALWAYS INCLUDE **BEFORE** GLFW)
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


GLuint generateVBO(GLuint vbo, GLsizeiptr size, const GLvoid * data);
GLuint generateVAO(GLuint vao, GLuint vbo, GLuint verticesPerDraw);
GLuint generateEBO(GLuint ebo, GLuint* indices);
void calculateNormals(GLfloat *vertices, int size);
void calculateNormals(GLfloat *vertices, int vertexSize, GLuint *indices, int indexSize);
// Vertices /**/ Texture coords /**/ Normals
   // Square vertices
   static GLfloat points[] = {
            0.5f, -0.5f, -1.0f,/**/  0.0f,  1.0f, /**/ 0.0, 0.0, 0.0,
            0.5f,  0.5f, -1.0f,/**/  1.0f,  1.0f, /**/ 0.0, 0.0, 0.0,
           -0.5f,  0.5f, -1.0f,/**/  1.0f,  0.0f, /**/ 0.0, 0.0, 0.0,
           -0.5f, -0.5f, -1.0f,/**/  0.0f,  0.0f, /**/ 0.0, 0.0, 0.0
   };

   static GLuint indices[] = {
           0, 1, 2,
           3, 0, 2
   };

   // Triangle vertices
   static GLfloat points2[] = {
            0.75f,-0.5f,-1.0f,/**/  0.0f, 0.0f, /**/ 0.0, 0.0, 0.0,
            1.0f,  0.0f,-1.0f,/**/  0.0f, 1.0f, /**/ 0.0, 0.0, 0.0,
            0.75f, 0.5f,-1.0f,/**/  1.0f, 0.0f, /**/ 0.0, 0.0, 0.0,

            0.5,  -0.75,-1.0f,/**/ -0.5,  0.0, /**/ 0.0, 0.0, 0.0,
           -0.5,  -0.75,-1.0f,/**/  0.5,  0.0, /**/ 0.0, 0.0, 0.0,
            0.0,  -1.0, -1.0f,/**/  0.0,  -1.0, /**/ 0.0, 0.0, 0.0,

           -0.75f, 0.5f,-1.0f,/**/ -0.75f, 0.5f, /**/ 0.0, 0.0, 0.0,
           -1.0f,  0.0f,-1.0f,/**/  -1.0f,  0.0f, /**/ 0.0, 0.0, 0.0,
           -0.75f,-0.5f,-1.0f,/**/  -0.75f,-0.5f, /**/ 0.0, 0.0, 0.0,

           -0.5,   0.75,-1.0f,/**/ -1.0, -1.0, /**/ 0.0, 0.0, 0.0,
            0.5,   0.75,-1.0f,/**/  1.0, -1.0, /**/ 0.0, 0.0, 0.0,
            0.0,   1.0, -1.0f,/**/  1.0, 1.0f, /**/ 0.0, 0.0, 0.0
   };

   // Cube vertices
//   static GLfloat cube[] = {
//           // Front
//           -0.25, 0.25, 0.0,/**/ 0.0, 1.0, /**/ 0.0, 0.0, 0.0, //0
//           -0.25,-0.25, 0.0,/**/ 1.0, 1.0, /**/ 0.0, 0.0, 0.0, //1
//            0.25,-0.25, 0.0,/**/ 1.0, 0.0, /**/ 0.0, 0.0, 0.0, //2
//
//            0.25,-0.25, 0.0,/**/ 1.0, 0.0, /**/ 0.0, 0.0, 0.0, //2
//            0.25, 0.25, 0.0,/**/ 0.0, 0.0, /**/ 0.0, 0.0, 0.0, //3
//           -0.25, 0.25, 0.0,/**/ 0.0, 1.0, /**/ 0.0, 0.0, 0.0, //0
//           // Back
//           -0.25, 0.25,-0.5,/**/ 0.0, 1.0, /**/ 0.0, 0.0, 0.0, //4
//            0.25, 0.25,-0.5,/**/ 1.0, 1.0, /**/ 0.0, 0.0, 0.0, //5
//            0.25,-0.25,-0.5,/**/ 1.0, 0.0, /**/ 0.0, 0.0, 0.0, //6
//
//            0.25,-0.25,-0.5,/**/ 1.0, 0.0, /**/ 0.0, 0.0, 0.0, //6
//           -0.25,-0.25,-0.5,/**/ 0.0, 0.0, /**/ 0.0, 0.0, 0.0, //7
//           -0.25, 0.25,-0.5,/**/ 0.0, 1.0, /**/ 0.0, 0.0, 0.0, //4
//           // Top
//           -0.25, 0.25, 0.0,/**/  0.0, 1.0, /**/ 0.0, 0.0, 0.0, //0
//            0.25, 0.25, 0.0,/**/  1.0, 1.0, /**/ 0.0, 0.0, 0.0, //3
//            0.25, 0.25,-0.5,/**/  1.0, 0.0, /**/ 0.0, 0.0, 0.0, //5
//
//            0.25, 0.25,-0.5,/**/  1.0, 0.0, /**/ 0.0, 0.0, 0.0, //5
//           -0.25, 0.25,-0.5,/**/  0.0, 0.0, /**/ 0.0, 0.0, 0.0, //4
//           -0.25, 0.25, 0.0,/**/  0.0, 1.0, /**/ 0.0, 0.0, 0.0, //0
//           // Bottom
//           -0.25,-0.25, 0.0,/**/  0.0, 1.0, /**/ 0.0, 0.0, 0.0, //1
//           -0.25,-0.25,-0.5,/**/  1.0, 1.0, /**/ 0.0, 0.0, 0.0, //7
//            0.25,-0.25,-0.5,/**/  1.0, 0.0, /**/ 0.0, 0.0, 0.0, //6
//
//            0.25,-0.25,-0.5,/**/  1.0, 0.0, /**/ 0.0, 0.0, 0.0, //6
//            0.25,-0.25, 0.0,/**/  0.0, 0.0, /**/ 0.0, 0.0, 0.0, //2
//           -0.25,-0.25, 0.0,/**/  0.0, 1.0, /**/ 0.0, 0.0, 0.0, //1
//           // Left
//           -0.25, 0.25, 0.0,/**/  1.0, 1.0, /**/ 0.0, 0.0, 0.0, //0
//           -0.25, 0.25,-0.5,/**/  0.0, 1.0, /**/ 0.0, 0.0, 0.0, //4
//           -0.25,-0.25,-0.5,/**/  0.0, 0.0, /**/ 0.0, 0.0, 0.0, //7
//
//           -0.25,-0.25,-0.5,/**/  0.0, 0.0, /**/ 0.0, 0.0, 0.0, //7
//           -0.25,-0.25, 0.0,/**/  1.0, 0.0, /**/ 0.0, 0.0, 0.0, //1
//           -0.25, 0.25, 0.0,/**/  1.0, 1.0, /**/ 0.0, 0.0, 0.0, //0
//           // Right
//            0.25, 0.25, 0.0,/**/  0.0, 1.0, /**/ 0.0, 0.0, 0.0, //3
//            0.25,-0.25, 0.0,/**/  1.0, 1.0, /**/ 0.0, 0.0, 0.0, //2
//            0.25,-0.25,-0.5,/**/  1.0, 0.0, /**/ 0.0, 0.0, 0.0, //6
//
//            0.25,-0.25,-0.5,/**/  1.0, 0.0, /**/ 0.0, 0.0, 0.0, //6
//            0.25, 0.25,-0.5,/**/  0.0, 0.0, /**/ 0.0, 0.0, 0.0, //5
//            0.25, 0.25, 0.0,/**/  0.0, 1.0, /**/ 0.0, 0.0, 0.0  //3
//   };

   static GLfloat cube[] = {
           -0.25, 0.25, 0.0,/**/ 0.0, 1.0, /**/ 0.0, 0.0, 0.0, //0
           -0.25,-0.25, 0.0,/**/ 1.0, 1.0, /**/ 0.0, 0.0, 0.0, //1
            0.25,-0.25, 0.0,/**/ 1.0, 0.0, /**/ 0.0, 0.0, 0.0, //2
            0.25, 0.25, 0.0,/**/ 0.0, 0.0, /**/ 0.0, 0.0, 0.0, //3
           -0.25, 0.25,-0.5,/**/ 1.0, 1.0, /**/ 0.0, 0.0, 0.0, //4
            0.25, 0.25,-0.5,/**/ 1.0, 1.0, /**/ 0.0, 0.0, 0.0, //5
            0.25,-0.25,-0.5,/**/ 0.0, 1.0, /**/ 0.0, 0.0, 0.0, //6
           -0.25,-0.25,-0.5,/**/ 0.0, 0.0, /**/ 0.0, 0.0, 0.0  //7
   };

   static GLuint indicesCube[] = {
           // Front
           0, 1, 2,
           2, 3, 0,
           // Back
           4, 5, 6,
           6, 7, 4,
           // Top
           0, 3, 5,
           5, 4, 0,
           // Bottom
           1, 7, 6,
           6, 2, 1,
           // Left
           0, 4, 7,
           7, 1, 0,
           // Right
           3, 2, 6,
           6, 5, 3
   };

#endif /* SRC_VERTICES_H_ */
