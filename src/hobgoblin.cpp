// Standard C/C++ libraries
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>

// OpenGL/Graphic libraries
// Include GLEW (ALWAYS INCLUDE **BEFORE** GLFW)
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Simple OpenGL Image Library, not sure if this library will be used
#include <SOIL.h>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Program libraries
#include "player.h"
#include "../system/diagnostics.h"
#include "graphics/shaders.h"
#include "graphics/vertices.h"
#include "graphics/textures.h"

int main() {

// GLFW initialization
   if (!glfwInit ()) {
	   fprintf (stderr, "ERROR: could not start GLFW3\n");
	   return 1;
   }

// Create window
   GLFWwindow* window = glfwCreateWindow(640, 640, "Hobgoblin", NULL, NULL);
   if (!window) {
       fprintf(stderr, "ERROR: could not open window with GLFW3\n");
       glfwTerminate();
       return 2;
   }
   glfwMakeContextCurrent (window);

// GLEW initialization
   glewExperimental = GL_TRUE;
   glewInit();

// Logging

   // print diagnostic info
    printDiagnosticInfo();

   // game log
   std::cout << "Hobgoblin starting..." << std::endl;
   std::cout << "Started!" << std::endl;
   std::cout << "Creating player..." << std::endl;
   Player* player = new Player();
   std::cout << "Done!" << std::endl;
   std::cout << "Player location at" << std::endl;
   std::cout << "X: " << player->getLocationX() << std::endl;
   std::cout << "Y: " << player->getLocationY() << std::endl;
   std::cout << "HP: " << player->getHp() << std::endl;
   std::cout << "Inventory initialized to empty." << std::endl;

   // tell GL to only draw onto a pixel if the shape is closer to the viewer
   glEnable(GL_DEPTH_TEST); // enable depth-testing
   glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
   // Cull triangles which normal is not towards the camera
//   glEnable(GL_CULL_FACE);

   // Vertex buffer objects
   GLuint vbo = 0;
   vbo = generateVBO(vbo, 30 * sizeof(float), points);
   GLuint vbo2 = 0;
   vbo2 = generateVBO(vbo2, 60 * sizeof(float), points2);
   GLuint vbo3 = 0;
   vbo3 = generateVBO(vbo3, 120 * sizeof(float), cube);

   // Vertex attribute objects
   GLuint vao = 0;
   vao = generateVAO(vao, vbo, 3);
   GLuint vao2 = 0;
   vao2 = generateVAO(vao2, vbo2, 3);
   GLuint vao3 = 0;
   vao3 = generateVAO(vao3, vbo3, 4);

   // Load shaders
   GLuint shader_program = loadShaders("shaders/vertex_shader_default.glsl", "shaders/fragment_shader_yellow.glsl");

   // Load textures
   GLuint texture = loadTexture("textures/wall.jpg");
   GLuint texture2 = loadTexture("textures/roof2.jpg");
   GLuint texture3 = loadTexture("textures/wooden_box.jpg");

   // Create background color by clearing
   glClearColor(0.2, 0.2, 0.2, 1);

   // Get a handle for our "MVP" uniform
//   GLuint MatrixID = glGetUniformLocation(shader_program, "MVP");

   //********************************************************************************************//
   //   Drawing loop                                                                             //
   //********************************************************************************************//
   while (!glfwWindowShouldClose (window)) {

       // wipe the drawing surface clear
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       // Wireframe or fill
//       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

       // Bind the texture
       glBindTexture(GL_TEXTURE_2D, texture);

       // Use 1st shader program with the 1st VAO
       glUseProgram(shader_program);

       glBindVertexArray(vao);
       glDrawArrays(GL_TRIANGLES, 0, 2*3); // draw 2 triangles

       // Bind the texture
       glBindTexture(GL_TEXTURE_2D, texture2);
       // Use 2nd shader program with the 2nd VAO
       glBindVertexArray(vao2);
       glDrawArrays(GL_TRIANGLES, 0, 4*3); // draw 4 triangles

//       // Bind the texture
//       glBindTexture(GL_TEXTURE_2D, texture3);
//       // Use 2nd shader program with the 3nd VAO
//       glBindVertexArray(vao3);
//       glDrawArrays(GL_QUADS, 0, 4); // draw 6 quads

       // cleanup
       glBindTexture(GL_TEXTURE_2D, 0);
       glBindVertexArray(0);

       // update other events like input handling
       glfwPollEvents();
       // put the stuff we've been drawing onto the display
       glfwSwapBuffers(window);
   }

   return 0;
}
