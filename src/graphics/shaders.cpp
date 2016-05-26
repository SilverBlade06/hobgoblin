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

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vs);
    glAttachShader(shader_program, fs);
    glLinkProgram(shader_program);

    glDetachShader(shader_program, vs);
    glDetachShader(shader_program, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return shader_program;
}
