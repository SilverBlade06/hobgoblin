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
#include "../system/diagnostics.h"
#include "controls/LightController.h"
//#include "controls/Controller.h"
#include "Camera.h"
#include "graphics/Light.h"
#include "graphics/Material.h"
#include "graphics/shaders.h"
#include "graphics/textures.h"
#include "graphics/vertices.h"
#include "Player.h"

GLint windowWidth = 640;
GLint windowHeight = 480;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

GLFWwindow* window;

// Create camera
Camera camera;

bool keys[1024];

// Callback declarations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void move(LightController *lightController);

int main() {

// GLFW initialization
   if (!glfwInit ()) {
	   std::cerr << "ERROR: could not start GLFW3" << std::endl;
	   return 1;
   }

   // Anti-aliasing
   glfwWindowHint(GLFW_SAMPLES, 4);

// Create window
   window = glfwCreateWindow(windowWidth, windowHeight, "Hobgoblin", NULL, NULL);
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
   Player player;
   std::cout << "Done!" << std::endl;
   std::cout << "Player location at" << std::endl;
   std::cout << "X: " << player.getLocationX() << std::endl;
   std::cout << "Y: " << player.getLocationY() << std::endl;
   std::cout << "HP: " << player.getHp() << std::endl;
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

   // Set the callback functions
   glfwSetKeyCallback(window, key_callback);
   glfwSetCursorPosCallback(window, mouse_callback);

   // Light source
   glm::vec3 lightPos = glm::vec3(0.2f, 0.6f, 1.25f);
   glm::vec3 ambient  = glm::vec3(1.0f, 1.0f, 1.0f);
   glm::vec3 diffuse  = glm::vec3(1.0f, 1.0f, 0.0f);
   glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f);
   Light light(lightPos, ambient, diffuse, specular);

   // Control the light
   LightController lightController(&light);

   // Material
   glm::vec3 materialAmbient  = glm::vec3(0.5f, 0.5f, 0.75f);
   glm::vec3 materialDiffuse  = glm::vec3(1.0f, 1.0f, 0.0f);
   glm::vec3 materialSpecular = glm::vec3(1.0f, 1.0f, 1.0f);
   GLfloat shininess = 128.0;
   Material material(
           materialAmbient,
           materialDiffuse,
           materialSpecular,
           shininess);

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

   // Draw the right picture at the start
   camera.handleControls(window, windowWidth, windowHeight, deltaTime);

   //********************************************************************************************//
   //   Drawing loop                                                                             //
   //********************************************************************************************//
   while (!glfwWindowShouldClose (window) && glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS) {

       // glfwGetTime is called only once, the first time this function is called
       static float lastTime = glfwGetTime();

       // Compute time difference between current and last frame
       float currentTime = glfwGetTime();
       deltaTime = float(currentTime - lastTime);

       // For the next frame, the "last time" will be "now"
       lastTime = currentTime;

       // update other events like input handling
       glfwPollEvents();

       // Clear the screen
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       // Wireframe or fill
//       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

       // Use the shader program
       glUseProgram(shader_program);

       // Camera position
       GLint cameraPosID = glGetUniformLocation(shader_program, "cameraPosition");
       glUniform3f(cameraPosID, camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);

       // Light position
       GLint lightPosID      = glGetUniformLocation(shader_program, "light.position");
       GLint lightAmbientID  = glGetUniformLocation(shader_program, "light.ambient");
       GLint lightDiffuseID  = glGetUniformLocation(shader_program, "light.diffuse");
       GLint lightSpecularID = glGetUniformLocation(shader_program, "light.specular");
       glUniform3f(lightPosID, light.getLightPos().x, light.getLightPos().y, light.getLightPos().z);
       glUniform3f(lightAmbientID, light.getAmbient().r, light.getAmbient().g, light.getAmbient().b);
       glUniform3f(lightDiffuseID, light.getDiffuse().r, light.getDiffuse().g, light.getDiffuse().b);
       glUniform3f(lightSpecularID, light.getSpecular().r, light.getSpecular().g, light.getSpecular().b);
       // Control light
//       lightController.control(window);

       // Material properties
       GLint materialAmbientID  = glGetUniformLocation(shader_program, "material.ambient");
       GLint materialDiffuseID  = glGetUniformLocation(shader_program, "material.diffuse");
       GLint materialSpecularID = glGetUniformLocation(shader_program, "material.specular");
       GLint materialShineID    = glGetUniformLocation(shader_program, "material.shininess");

       glUniform3f(materialAmbientID,  material.getAmbient().r, material.getAmbient().g, material.getAmbient().b);
       glUniform3f(materialDiffuseID,  material.getDiffuse().r, material.getDiffuse().g, material.getDiffuse().b);
       glUniform3f(materialSpecularID, material.getSpecular().r, material.getSpecular().g, material.getSpecular().b);
       glUniform1f(materialShineID,    material.getShininess());

       // Control and camera management
       move(&lightController);

       glm::mat4 ProjectionMatrix = camera.getProjectionMatrix();
       glm::mat4 ViewMatrix = camera.getViewMatrix();
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

       // put the stuff we've been drawing onto the display
       glfwSwapBuffers(window);
   }

   return 0;
}

// Callback methods

void move(LightController *lightController){
   // Camera controls
   if(keys[GLFW_KEY_W] || keys[GLFW_KEY_S] || keys[GLFW_KEY_A] || keys[GLFW_KEY_D] || keys[GLFW_KEY_SPACE])
       camera.handleControls(window, windowWidth, windowHeight, deltaTime);
   if(keys[GLFW_KEY_I] || keys[GLFW_KEY_K] || keys[GLFW_KEY_J] || keys[GLFW_KEY_L] || keys[GLFW_KEY_O] || keys[GLFW_KEY_U])
       lightController->control(window, deltaTime);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024){
        if(action == GLFW_PRESS) {
            keys[key] = true;
            std::cout << key << " has been pressed." << std::endl;
        }
        else if(action == GLFW_RELEASE){
            keys[key] = false;
            std::cout << key << " has been released." << std::endl;
        }
    }
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos){
    camera.handleControls(window, windowWidth, windowHeight, deltaTime);
}
