#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "player.h"

//using namespace std;

// Include GLEW (ALWAYS INCLUDE **BEFORE** GLFW
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Simple OpenGL Image Library
#include <SOIL.h>

int main(/*int argc, char **argv*/) {

// GLFW initialization
   if (!glfwInit ()) {
	   fprintf (stderr, "ERROR: could not start GLFW3\n");
	   return 1;
   }

// Create window
   GLFWwindow* window = glfwCreateWindow (640, 640, "Hobgoblin", NULL, NULL);
   if (!window) {
       fprintf (stderr, "ERROR: could not open window with GLFW3\n");
       glfwTerminate();
       return 1;
   }
   glfwMakeContextCurrent (window);

// GLEW initialization
   glewExperimental = GL_TRUE;
   glewInit();

// Logging

   // get version info
   const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
   const GLubyte* version = glGetString(GL_VERSION); // version as a string
   printf ("Renderer: %s\n", renderer);
   printf ("OpenGL version supported %s\n", version);

   // Experimenting
   GLint numberOfMaxAttributes;
   glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numberOfMaxAttributes);
   std::cout << "Maximum number of vertex attributes supported: " << numberOfMaxAttributes << std::endl;

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
   glEnable (GL_DEPTH_TEST); // enable depth-testing
   glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"

   // Square vertices /**/ Texture coords
   float points[] = {
	    -0.5f,  0.5f,  0.0f,/**/ -1.0f,  1.0f,
		 0.5f,  0.5f,  0.0f,/**/  1.0f,  1.0f,
	     0.5f, -0.5f,  0.0f,/**/  1.0f, -1.0f,
		-0.5f, -0.5f,  0.0f,/**/ -1.0f, -1.0f,
		 0.5f, -0.5f,  0.0f,/**/  1.0f, -1.0f,
	    -0.5f,  0.5f,  0.0f,/**/ -1.0f,  1.0f
   };

   // Texture points
//   float texture_points[] = {
//           -0.5f,  0.5f,
//            0.5f,  0.5f,
//            0.5f, -0.5f,
//           -0.5f, -0.5f,
//            0.5f, -0.5f,
//           -0.5f,  0.5f
//   };

   // Triangle vertices
   float points2[] = {
		 0.75f, 0.5f, 0.0f,/**/ 0.5f, 0.5f,
	     1.0f,  0.0f, 0.0f,/**/  0.5f, -0.5f,
		 0.75f,-0.5f, 0.0f,/**/  1.0f, 0.0f,
		-0.5,  -0.75, 0.0,/**/ -0.5,  -0.75,
		 0.5,  -0.75, 0.0,/**/  0.5,  -0.75,
		 0.0,  -1.0,  0.0,/**/  0.0,  -1.0,
		-0.75f, 0.5f, 0.0f,/**/ -0.75f, 0.5f,
		-1.0f,  0.0f, 0.0f,/**/  -1.0f,  0.0f,
		-0.75f,-0.5f, 0.0f,/**/  -0.75f,-0.5f,
		-0.5,   0.75, 0.0,/**/ -1.0, -1.0,
	     0.5,   0.75, 0.0,/**/  1.0, -1.0,
		 0.0,   1.0,  0.0,/**/  1.0, 1.0f
   };

   // Vertex buffer objects
   GLuint vbo;
   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, 30 * sizeof (float), points, GL_STATIC_DRAW);

   GLuint vbo2;
   glGenBuffers(1, &vbo2);
   glBindBuffer(GL_ARRAY_BUFFER, vbo2);
   glBufferData(GL_ARRAY_BUFFER, 60 * sizeof (float), points2, GL_STATIC_DRAW);

   // Vertex attribute objecs
   GLuint vao;
   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);
//   glEnableVertexAttribArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   // Vertices
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof (float), NULL);
   glEnableVertexAttribArray(0);
   // Texture coords
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof (float), (GLvoid*)(3 * sizeof (float)));
   glEnableVertexAttribArray(1);

   GLuint vao2;
   glGenVertexArrays(1, &vao2);
   glBindVertexArray(vao2);
   glBindBuffer(GL_ARRAY_BUFFER, vbo2);
   // Vertices
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof (float), NULL);
   glEnableVertexAttribArray(0);
   // Texture coords
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof (float), (GLvoid*)(3 * sizeof (float)));
   glEnableVertexAttribArray(1);

   // Read the Vertex Shader code from the file
   std::string VertexShaderCode;
   std::ifstream VertexShaderStream("shaders/vertex_shader_default.glsl", std::ios::in);
   if (VertexShaderStream.is_open()){
       std::string Line = "";
       while(getline(VertexShaderStream, Line))
       	   VertexShaderCode += "\n" + Line;
     	   VertexShaderStream.close();
   } else {
   	   printf("Impossible to open Vertex shader!");
       getchar();
       return 0;
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
   }

   const char* fragment_shader2 = FragmentShaderCode2.c_str();

   // Create and compile shaders
   GLuint vs = glCreateShader (GL_VERTEX_SHADER);
   glShaderSource (vs, 1, &vertex_shader, NULL);
   glCompileShader (vs);
   GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
   glShaderSource (fs, 1, &fragment_shader, NULL);
   glCompileShader (fs);
   GLuint fs2 = glCreateShader (GL_FRAGMENT_SHADER);
   glShaderSource (fs2, 1, &fragment_shader2, NULL);
   glCompileShader (fs2);

   GLuint shader_program = glCreateProgram ();
   glAttachShader (shader_program, fs);
   glAttachShader (shader_program, vs);
   glLinkProgram (shader_program);

   GLuint shader_program2 = glCreateProgram ();
   glAttachShader (shader_program2, fs2);
   glAttachShader (shader_program2, vs);
   glLinkProgram (shader_program2);

   // Textures
   GLfloat texCoords[] = {
       0.0f, 0.0f,
       1.0f, 0.0f,
       0.0f, 1.0f
   };

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
      unsigned char* image2 = SOIL_load_image("textures/roof.jpg", &width2, &height2, 0, SOIL_LOAD_RGB);

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
      glGenerateMipmap(GL_TEXTURE_2D);
      SOIL_free_image_data(image2);
      glBindTexture(GL_TEXTURE_2D, 0);

   // Create background color by clearing
   glClearColor(0.2, 0.2, 0.2, 1);

   // Drawing loop
   while (!glfwWindowShouldClose (window)) {
       // wipe the drawing surface clear
       glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       // Wireframe or fill
   //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

       // Bind the texture
       glBindTexture(GL_TEXTURE_2D, texture);
       // Use 1st shader program with the 1st VAO
       glUseProgram(shader_program);
       glBindVertexArray(vao);

       // draw points 0-3 from the currently bound VAO with current in-use shader
       glDrawArrays(GL_TRIANGLES, 0, 2*3); // draw 2 triangles

       // Bind the texture
       glBindTexture(GL_TEXTURE_2D, texture2);
       // Use 2nd shader program with the 2nd VAO
       glUseProgram (shader_program2);
       glBindVertexArray (vao2);
       glDrawArrays(GL_TRIANGLES, 0, 4*3); // draw 4 triangles

       // update other events like input handling
       glfwPollEvents ();
       // put the stuff we've been drawing onto the display
       glfwSwapBuffers (window);
   }

   return 0;
}
