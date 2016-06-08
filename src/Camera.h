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
   glm::mat4 getProjectionMatrix();
   glm::vec3 getPosition();
   GLfloat getHorizontalAngle();
   GLfloat getVerticalAngle();
   GLfloat getFoV();
   void handleControls(GLFWwindow* window, GLfloat windowWidth, GLfloat windowHeight);
   ~Camera();

   GLfloat getFov() const {
       return fov;
   }

   void setFov(GLfloat fov) {
       this->fov = fov;
   }

   void setHorizontalAngle(GLfloat horizontalAngle) {
       this->horizontalAngle = horizontalAngle;
   }

   void setPosition(const glm::vec3& position) {
       this->position = position;
   }

   void setProjectionMatrix(const glm::mat4& projectionMatrix) {
       ProjectionMatrix = projectionMatrix;
   }

   void setVerticalAngle(GLfloat verticalAngle) {
       this->verticalAngle = verticalAngle;
   }

   void setViewMatrix(const glm::mat4& viewMatrix) {
       ViewMatrix = viewMatrix;
   }
};

#endif /* SRC_CAMERA_H_ */
