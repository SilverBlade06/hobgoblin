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

// Program libraries
#include "player.h"
#include "../system/diagnostics.h"
#include "vertices.h"

// 3D vector structure
struct Vector {
   float x, y, z;

   Vector() {
       x = 0;
       y = 0;
       z = 0;
   }

   Vector(float x, float y, float z = 0) {
       this->x = x;
       this->y = y;
       this->z = z;
   }

   Vector operator*(float a) {
       return Vector(x * a, y * a, z * a);
   }

   Vector operator/(float a) {
          return Vector(x / a, y / a, z / a);
   }

   Vector operator+(const Vector& v) {
       return Vector(x + v.x, y + v.y, z + v.z);
   }

   Vector operator-(const Vector& v) {
       return Vector(x - v.x, y - v.y, z - v.z);
   }

   float operator*(const Vector& v) {
       return (x * v.x + y * v.y + z * v.z);
   }

   Vector operator%(const Vector& v) {
       return Vector(y*v.z-z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
   }

   float length() {
       return sqrt(x * x + y * y + z * z);
   }
};

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

const char* loadShaderFromFile(const char* filePath) {
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(filePath, std::ios::in);
    if (VertexShaderStream.is_open()) {
        std::string Line = "";
        while (getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    } else {
        printf("Impossible to open shader!");
        getchar();
    }
    const char* vertex_shader = VertexShaderCode.c_str();
    return vertex_shader;
}

//********************************************************************************************//
//   Camera, Controls, keyboard and mouse                                                TODO //
//********************************************************************************************//

// horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// vertical angle : 0, look at the horizon
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;

Vector cameraPos(0,0,5);
Vector cameraDirection;
Vector cameraRight(
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        cos(horizontalAngle - 3.14f/2.0f));
Vector cameraUp = (cameraDirection % cameraRight) / ((cameraDirection % cameraRight)).length();

double lastTime = glfwGetTime();

void handleCameraView(GLFWwindow* window) {

   double currentTime = glfwGetTime();
   double deltaTime = double(currentTime - lastTime);

   // Get mouse position
   double xpos, ypos;
   glfwGetCursorPos(window, &xpos, &ypos);

   // Reset mouse position for next frame
   glfwSetCursorPos(window, 640/2, 640/2);

   // Compute new orientation
   horizontalAngle = horizontalAngle + mouseSpeed * deltaTime * float(640/2 - xpos);
   verticalAngle   = verticalAngle + mouseSpeed * deltaTime * float(640/2 - ypos);

   cameraDirection.x = cos(verticalAngle) * sin(horizontalAngle);
   cameraDirection.y = sin(verticalAngle);
   cameraDirection.z = cos(verticalAngle) * cos(horizontalAngle);

   cameraRight.x = sin(horizontalAngle - 3.14f/2.0f);
   cameraRight.y = 0;
   cameraRight.z = cos(horizontalAngle - 3.14f/2.0f);

   cameraUp = (cameraDirection % cameraRight) / ((cameraDirection % cameraRight)).length();

   // Move forward
   if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
       cameraPos = cameraPos + cameraDirection * deltaTime * speed;
   }
   // Move backward
   if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
       cameraPos = cameraPos - cameraDirection * deltaTime * speed;
   }
   // Strafe right
   if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
       cameraPos = cameraPos + cameraRight * deltaTime * speed;
   }
   // Strafe left
   if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
       cameraPos = cameraPos - cameraRight * deltaTime * speed;
   }

   gluLookAt(
           cameraPos.x,
           cameraPos.y,
           cameraPos.z,
           cameraPos.x + cameraDirection.x,
           cameraPos.x + cameraDirection.y,
           cameraPos.x + cameraDirection.z,
           cameraUp.x,
           cameraUp.y,
           cameraUp.z);

//   // Projection matrix : 45&deg; Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
//   ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
//   // Camera matrix
//   ViewMatrix       = glm::lookAt(
//       position,           // Camera is here
//       position+direction, // and looks here : at the same position, plus "direction"
//       up                  // Head is up (set to 0,-1,0 to look upside-down)
//   );

   lastTime = currentTime;

}

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

   // Read the Vertex Shader code from the file
//   const char* vertex_shader = loadShaderFromFile("shaders/vertex_shader_default.glsl");
//   const char* fragment_shader = loadShaderFromFile("shaders/fragment_shader_yellow.glsl");
//   const char* fragment_shader2 = loadShaderFromFile("shaders/fragment_shader_green.glsl");
   std::string VertexShaderCode;
   std::ifstream VertexShaderStream("shaders/vertex_shader_default.glsl", std::ios::in);
   if (VertexShaderStream.is_open()) {
       std::string Line = "";
       while (getline(VertexShaderStream, Line))
           VertexShaderCode += "\n" + Line;
       VertexShaderStream.close();
   } else {
       printf("Impossible to open shader!");
       getchar();
   }

   const char* vertex_shader = VertexShaderCode.c_str();
   // Read the Fragment Shader code from the file
   std::string FragmentShaderCode;
   std::ifstream FragmentShaderStream("shaders/fragment_shader_yellow.glsl", std::ios::in);
   if (FragmentShaderStream.is_open()){
       std::string Line = "";
       while(getline(FragmentShaderStream, Line))
     	   FragmentShaderCode += "\n" + Line;
     	   FragmentShaderStream.close();
   } else {
       printf("Impossible to open Fragment shader!");
       getchar();
//       return 0;
   }

   const char* fragment_shader = FragmentShaderCode.c_str();

   // Read the second Fragment Shader code from the file
   std::string FragmentShaderCode2;
   std::ifstream FragmentShaderStream2("shaders/fragment_shader_green.glsl", std::ios::in);
   if (FragmentShaderStream2.is_open()){
       std::string Line = "";
       while(getline(FragmentShaderStream2, Line))
           FragmentShaderCode2 += "\n" + Line;
     	   FragmentShaderStream2.close();
   } else {
       printf("Impossible to open Fragment shader!");
       getchar();
//       return 0;
   }

   const char* fragment_shader2 = FragmentShaderCode2.c_str();

   // Create and compile shaders
   GLuint vs = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vs, 1, &vertex_shader, NULL);
   glCompileShader(vs);
   GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fs, 1, &fragment_shader, NULL);
   glCompileShader(fs);
   GLuint fs2 = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fs2, 1, &fragment_shader2, NULL);
   glCompileShader(fs2);

   GLuint shader_program = glCreateProgram();
   glAttachShader(shader_program, fs);
   glAttachShader(shader_program, vs);
   glLinkProgram(shader_program);

   GLuint shader_program2 = glCreateProgram();
   glAttachShader(shader_program2, fs2);
   glAttachShader(shader_program2, vs);
   glLinkProgram(shader_program2);

   // Texture No. 1

   GLuint texture; // texture ID
   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);
   // Parameters
   // Texture wrap
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   // Texture filter
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   // Only for Mipmaps
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   int width, height;
   unsigned char* image = SOIL_load_image("textures/wall.jpg", &width, &height, 0, SOIL_LOAD_RGB);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
   glGenerateMipmap(GL_TEXTURE_2D);
   // Cleanup
   SOIL_free_image_data(image);
   glBindTexture(GL_TEXTURE_2D, 0);

   // Texture No. 2

   GLuint texture2; // texture ID
   glGenTextures(1, &texture2);
   glBindTexture(GL_TEXTURE_2D, texture2);
   // Parameters
   // Texture wrap
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   // Texture filter
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   // Only for Mipmaps
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   int width2, height2;
   unsigned char* image2 = SOIL_load_image("textures/roof2.jpg", &width2, &height2, 0, SOIL_LOAD_RGB);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
   glGenerateMipmap(GL_TEXTURE_2D);
   // Cleanup
   SOIL_free_image_data(image2);
   glBindTexture(GL_TEXTURE_2D, 0);

   // Texture No. 3 BOX

   GLuint texture3; // texture ID
   glGenTextures(1, &texture3);
   glBindTexture(GL_TEXTURE_2D, texture3);
   // Parameters
   // Texture wrap
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   // Texture filter
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   // Only for Mipmaps
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   int width3, height3;
   unsigned char* image3 = SOIL_load_image("textures/wooden_box.jpg", &width3, &height3, 0, SOIL_LOAD_RGB);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width3, height3, 0, GL_RGB, GL_UNSIGNED_BYTE, image3);
   glGenerateMipmap(GL_TEXTURE_2D);
   // Cleanup
   SOIL_free_image_data(image3);
   glBindTexture(GL_TEXTURE_2D, 0);

   //********************************************************************************************//
   //   Drawing loop                                                                             //
   //********************************************************************************************//
   while (!glfwWindowShouldClose (window)) {

       glEnable(GL_DEPTH_TEST);
       // wipe the drawing surface clear
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       // Create background color by clearing
       glClearColor(0.2, 0.2, 0.2, 1);

       // Wireframe or fill
//       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//       handleCameraView(window); // TODO, doesn't work for now

       // Bind the texture
       glBindTexture(GL_TEXTURE_2D, texture);
       // Use 1st shader program with the 1st VAO
       glUseProgram(shader_program);
       glBindVertexArray(vao);
       glDrawArrays(GL_TRIANGLES, 0, 2*3); // draw 2 triangles

       // Bind the texture
       glBindTexture(GL_TEXTURE_2D, texture2);
       // Use 2nd shader program with the 2nd VAO
       glUseProgram(shader_program2);
       glBindVertexArray(vao2);
       glDrawArrays(GL_TRIANGLES, 0, 4*3); // draw 4 triangles
//gluLookAt(0.2,0.3,0,0,0,-0.5,0,1,0);
//       // Bind the texture
//       glBindTexture(GL_TEXTURE_2D, texture3);
//       // Use 2nd shader program with the 3nd VAO
//       glUseProgram(shader_program);
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
