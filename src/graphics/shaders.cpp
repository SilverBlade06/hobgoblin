/*
 * shaders.cpp
 *
 *  Created on: 2016. máj. 23.
 *      Author: SilverBlade
 */

// Include GLEW (ALWAYS INCLUDE **BEFORE** GLFW)

#include "../graphics/shaders.h"

std::string loadShaderFromFile(const char* filePath) {
   std::string shaderCode;
   std::ifstream shaderStream(filePath, std::ios::in);
   if (shaderStream.is_open()) {
       std::string Line = "";
       while (getline(shaderStream, Line))
           shaderCode += "\n" + Line;
       shaderStream.close();
   } else {
       std::cerr << "Impossible to open shader!" << std::endl;
       getchar();
   }

    return shaderCode;
}

GLuint loadShaders(const char * vertex_file_path, const char * fragment_file_path){
   std::string vertexShaderCode = loadShaderFromFile(vertex_file_path);
   std::string fragmentShaderCode = loadShaderFromFile(fragment_file_path);

   const char* vertex_shader = vertexShaderCode.c_str();
   const char* fragment_shader = fragmentShaderCode.c_str();

   GLint success;
   GLchar infoLog[512];

   GLuint vs = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vs, 1, &vertex_shader, NULL);
   glCompileShader(vs);

   // Print compile errors if any
   glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
   if (!success){
       glGetShaderInfoLog(vs, 512, NULL, infoLog);
       std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
   }

   GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fs, 1, &fragment_shader, NULL);
   glCompileShader(fs);

   // Print compile errors if any
   glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
   if (!success) {
       glGetShaderInfoLog(fs, 512, NULL, infoLog);
       std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
   }

   GLuint shader_program = glCreateProgram();
   glAttachShader(shader_program, vs);
   glAttachShader(shader_program, fs);
   glLinkProgram(shader_program);

   // Print linking errors if any
   glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
   if (!success) {
       glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
       std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
   }

   glDetachShader(shader_program, vs);
   glDetachShader(shader_program, fs);

   glDeleteShader(vs);
   glDeleteShader(fs);

   return shader_program;
}
