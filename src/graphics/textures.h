#ifndef SRC_GRAPHICS_TEXTURES_H_
#define SRC_GRAPHICS_TEXTURES_H_

#include <fstream>

// Include GLEW (ALWAYS INCLUDE **BEFORE** GLFW)
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Simple OpenGL Image Library, not sure if this library will be used
#include <SOIL.h>

GLuint loadTexture(const char* texture_file_path);

#endif /* SRC_GRAPHICS_TEXTURES_H_ */
