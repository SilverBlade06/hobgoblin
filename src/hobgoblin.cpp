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
#include <glm/gtc/type_ptr.hpp>

// Program libraries
#include "player.h"
#include "../system/diagnostics.h"
#include "controls/lightController.h"
#include "graphics/shaders.h"
#include "graphics/vertices.h"
#include "graphics/textures.h"
#include "graphics/light.h"
#include "camera.h"

int main() {

// GLFW initialization
   if (!glfwInit ()) {
	   std::cerr << "ERROR: could not start GLFW3" << std::endl;
	   return 1;
   }

   // Anti-aliasing
   glfwWindowHint(GLFW_SAMPLES, 4);

// Create window
   int windowWidth = getWindowWidth();
   int windowHeight = getWindowHeight();
   GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Hobgoblin", NULL, NULL);
   if (!window) {
       std::cerr << "ERROR: could not open window with GLFW3" << std::endl;
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
   glEnable(GL_CULL_FACE);

   // Ensure we can capture the escape key being pressed below
   glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
   // Hide the mouse and enable unlimited movement
   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   // Set the mouse at the center of the screen
   glfwPollEvents();
   glfwSetCursorPos(window, windowWidth/2, windowHeight/2);

   // Load shaders
   GLuint shader_program = loadShaders(
           "shaders/vertex_shader_default.glsl",
           "shaders/fragment_shader_yellow.glsl");

   // Light source
   glm::vec3 lightPos = glm::vec3(0.2f, 0.6f, 1.25f);
   glm::vec3 ambient  = glm::vec3(1.0f, 1.0f, 0.0f);
   glm::vec3 diffuse  = glm::vec3(1.0f, 1.0f, 0.0f);
   glm::vec3 specular = glm::vec3(1.0f, 1.0f, 0.0f);
   Light* light = new Light(lightPos, ambient, diffuse, specular);

   // Control the light
   LightController *lightController = new LightController(window, light);

   // Get a handle for our "MVP" uniform, MVPID = Model/View/Projection Matrix ID
   GLuint MVPID = glGetUniformLocation(shader_program, "MVP");
   GLuint ModelID = glGetUniformLocation(shader_program, "Model");

   // Load textures
   GLuint texture  = loadTexture("textures/wall.jpg");
   GLuint texture2 = loadTexture("textures/roof2.jpg");
   GLuint texture3 = loadTexture("textures/wooden_box.jpg");

   // Calculate normal vectors
   calculateNormals(points, 2);
   calculateNormals(points2, 4);
   calculateNormals(cube, 12);

   // Vertex buffer objects
   GLuint vbo = 0;
   vbo = generateVBO(vbo, 48 * sizeof(GLfloat), points);
   GLuint vbo2 = 0;
   vbo2 = generateVBO(vbo2, 96 * sizeof(GLfloat), points2);
   GLuint vbo3 = 0;
   vbo3 = generateVBO(vbo3, 288 * sizeof(GLfloat), cube);

   // Vertex attribute objects
   GLuint vao = 0;
   vao = generateVAO(vao, vbo, 3);
   GLuint vao2 = 0;
   vao2 = generateVAO(vao2, vbo2, 3);
   GLuint vao3 = 0;
   vao3 = generateVAO(vao3, vbo3, 3);

   // Create background color by clearing
   glClearColor(0.2, 0.2, 0.2, 1);

   //********************************************************************************************//
   //   Drawing loop                                                                             //
   //********************************************************************************************//
   while (!glfwWindowShouldClose (window) && glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS) {

       // Clear the screen
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       // Wireframe or fill
//       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

       // Use the shader program
       glUseProgram(shader_program);

       // Camera position
       GLint cameraPosID = glGetUniformLocation(shader_program, "cameraPosition");
       glUniform3f(cameraPosID, getCameraPosition().x, getCameraPosition().y, getCameraPosition().z);

       // Light position
       GLint lightPosID = glGetUniformLocation(shader_program, "lightPos");
       glUniform3f(lightPosID, light->getLightPos().x, light->getLightPos().y, light->getLightPos().z);
       // Control light
       lightController->control();

       // Material properties
       GLint materialAmbientID  = glGetUniformLocation(shader_program, "material.ambient");
       GLint materialDiffuseID  = glGetUniformLocation(shader_program, "material.diffuse");
       GLint materialSpecularID = glGetUniformLocation(shader_program, "material.specular");
       GLint materialShineID    = glGetUniformLocation(shader_program, "material.shininess");

       glUniform3f(materialAmbientID,  0.5f, 0.5f, 0.75f);
       glUniform3f(materialDiffuseID,  1.0f, 1.0f, 0.0f);
       glUniform3f(materialSpecularID, 1.0f, 1.0f, 1.0f);
       glUniform1f(materialShineID,    128.0f);

       // Control and camera management
       handleControls(window);
       glm::mat4 ProjectionMatrix = getProjectionMatrix();
       glm::mat4 ViewMatrix = getViewMatrix();
       glm::mat4 ModelMatrix = glm::mat4(1.0);
       glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

       // Send our transformation to the currently bound shader, in the "MVP" uniform
       glUniformMatrix4fv(MVPID, 1, GL_FALSE, glm::value_ptr(MVP));
       glUniformMatrix4fv(ModelID, 1, GL_FALSE, glm::value_ptr(ModelMatrix));

       // Bind the texture
       glBindTexture(GL_TEXTURE_2D, texture);

       glBindVertexArray(vao);
       glDrawArrays(GL_TRIANGLES, 0, 2*3); // draw 2 triangles

       // Bind the texture
       glBindTexture(GL_TEXTURE_2D, texture2);
       // Use 2nd shader program with the 2nd VAO
       glBindVertexArray(vao2);
       glDrawArrays(GL_TRIANGLES, 0, 4*3); // draw 4 triangles

       // Bind the texture
       glBindTexture(GL_TEXTURE_2D, texture3);
       // Use 2nd shader program with the 3nd VAO
       glBindVertexArray(vao3);
       glDrawArrays(GL_TRIANGLES, 0, 12*3); // draw 12 triangles

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
