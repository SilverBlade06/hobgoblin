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

class Camera {
private:
   glm::mat4 ViewMatrix;
   glm::mat4 ProjectionMatrix;

   glm::vec3 position;
   GLfloat horizontalAngle;
   GLfloat verticalAngle;
   GLfloat fov;
public:
   Camera();
   Camera(glm::vec3 position, GLfloat horizontalAngle, GLfloat verticalAngle, GLfloat fov);
   glm::mat4 getViewMatrix();
   void setViewMatrix(const glm::mat4& viewMatrix);
   glm::mat4 getProjectionMatrix();
   void setProjectionMatrix(const glm::mat4& projectionMatrix);

   glm::vec3 getPosition();
   void setPosition(const glm::vec3& position);
   GLfloat getHorizontalAngle();
   void setHorizontalAngle(GLfloat horizontalAngle);
   GLfloat getVerticalAngle();
   void setVerticalAngle(GLfloat verticalAngle);
   GLfloat getFov() const;
   void setFov(GLfloat fov);
   void handleControls(GLFWwindow* window, GLfloat windowWidth, GLfloat windowHeight, float deltaTime);
   ~Camera();
};

#endif /* SRC_CAMERA_H_ */
