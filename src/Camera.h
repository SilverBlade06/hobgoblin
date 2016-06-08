#include <iostream>

// OpenGL/Graphic libraries
// Include GLEW (ALWAYS INCLUDE **BEFORE** GLFW)
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_

int getWindowWidth();
int getWindowHeight();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
glm::vec3 getCameraPosition();
void handleControls(GLFWwindow* window);

#endif /* SRC_CAMERA_H_ */
