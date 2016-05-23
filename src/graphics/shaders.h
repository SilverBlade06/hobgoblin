/*
 * shaders.h
 *
 *  Created on: 2016. máj. 23.
 *      Author: SilverBlade
 */

#ifndef SRC_GRAPHICS_SHADERS_H_
#define SRC_GRAPHICS_SHADERS_H_

#include <fstream>

// Include GLEW (ALWAYS INCLUDE **BEFORE** GLFW)
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>

/**
 * Load vertex and fragment shaders from file to create shader program.
 */
GLuint loadShaders(const char * vertex_file_path, const char * fragment_file_path);

#endif /* SRC_GRAPHICS_SHADERS_H_ */
