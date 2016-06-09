//********************************************************************************************//
//   Camera, Controls, keyboard and mouse                                                     //
//********************************************************************************************//
#include "Camera.h"

extern bool keys[1024];

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;

glm::mat4 Camera::getViewMatrix() {
   return ViewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() {
   return ProjectionMatrix;
}

glm::vec3 Camera::getPosition() {
   return position;
}

GLfloat Camera::getHorizontalAngle(){
   return horizontalAngle;
}

GLfloat Camera::getVerticalAngle(){
   return verticalAngle;
}

GLfloat Camera::getFov() const {
   return fov;
}

void Camera::setFov(GLfloat fov) {
   this->fov = fov;
}

void Camera::setHorizontalAngle(GLfloat horizontalAngle) {
   this->horizontalAngle = horizontalAngle;
}

void Camera::setPosition(const glm::vec3& position) {
   this->position = position;
}

void Camera::setProjectionMatrix(const glm::mat4& projectionMatrix) {
   ProjectionMatrix = projectionMatrix;
}

void Camera::setVerticalAngle(GLfloat verticalAngle) {
   this->verticalAngle = verticalAngle;
}

void Camera::setViewMatrix(const glm::mat4& viewMatrix) {
   ViewMatrix = viewMatrix;
}

Camera::Camera() {
   this->position = glm::vec3(0, 0, 3);
   this->horizontalAngle = 3.14f;
   this->verticalAngle = 0.0f;
   this->fov = 45.0f;
}

Camera::Camera(glm::vec3 position, GLfloat horizontalAngle, GLfloat verticalAngle, GLfloat fov) {
   this->position = position;
   this->horizontalAngle = horizontalAngle;
   this->verticalAngle = verticalAngle;
   this->fov = fov;
}

void Camera::handleControls(GLFWwindow* window, GLfloat windowWidth, GLfloat windowHeight, float deltaTime) {
//    // glfwGetTime is called only once, the first time this function is called
//   static double lastTime = glfwGetTime();
//
//   // Compute time difference between current and last frame
//   double currentTime = glfwGetTime();
//   float deltaTime = float(currentTime - lastTime);

   // Get mouse position
   double xpos, ypos;
   glfwGetCursorPos(window, &xpos, &ypos);

   // Reset mouse position for next frame
   glfwSetCursorPos(window, windowWidth/2, windowHeight/2);

   // Compute new orientation
   horizontalAngle = horizontalAngle + mouseSpeed * GLfloat(windowWidth/2 - xpos);
   verticalAngle   = verticalAngle   + mouseSpeed * GLfloat(windowHeight/2 - ypos);

   // Direction : Spherical coordinates to Cartesian coordinates conversion
   glm::vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
   );

   // Right vector
   glm::vec3 rightVec = glm::vec3(
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        cos(horizontalAngle - 3.14f/2.0f)
   );

   // Up vector
   glm::vec3 upVec = glm::cross(rightVec, direction);

   // Move forward
   if (keys[GLFW_KEY_W]) {
        position = position + direction * deltaTime * speed;
        std::cout << "Position  x: " << position.x << " y: " << position.y << " z: " << position.z << std::endl;
   }
   // Move backward
   if (keys[GLFW_KEY_S]) {
        position = position - direction * deltaTime * speed;
        std::cout << "Position  x: " << position.x << " y: " << position.y << " z: " << position.z << std::endl;
   }
   // Strafe right
   if (keys[GLFW_KEY_D]) {
        position = position + rightVec * deltaTime * speed;
        std::cout << "Position  x: " << position.x << " y: " << position.y << " z: " << position.z << std::endl;
   }
   // Strafe left
   if (keys[GLFW_KEY_A]) {
        position = position - rightVec * deltaTime * speed;
        std::cout << "Position  x: " << position.x << " y: " << position.y << " z: " << position.z << std::endl;
   }
   // Go up
   if (keys[GLFW_KEY_SPACE]) {
        position = position + upVec * deltaTime * speed;
        std::cout << "Position  x: " << position.x << " y: " << position.y << " z: " << position.z << std::endl;
   }

   // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
   ProjectionMatrix = glm::perspective(glm::radians(fov), (GLfloat)windowWidth / (GLfloat)windowHeight, 0.1f, 100.0f);
   // Camera matrix
   ViewMatrix       = glm::lookAt(
           position,             // Camera is here
           position + direction, // and looks here : at the same position, plus "direction"
           upVec                 // Head is up (set to 0,-1,0 to look upside-down)
   );

}

//void Camera::keyboardMove(CameraMovement direction) {
//   // glfwGetTime is called only once, the first time this function is called
//   static double lastTime = glfwGetTime();
//
//   // Compute time difference between current and last frame
//   double currentTime = glfwGetTime();
//   float deltaTime = float(currentTime - lastTime);
//
//   // Direction : Spherical coordinates to Cartesian coordinates conversion
//   glm::vec3 moveDirection(
//       cos(verticalAngle) * sin(horizontalAngle),
//       sin(verticalAngle),
//       cos(verticalAngle) * cos(horizontalAngle)
//   );
//
//   // Right vector
//   glm::vec3 rightVec = glm::vec3(
//       sin(horizontalAngle - 3.14f/2.0f),
//       0,
//       cos(horizontalAngle - 3.14f/2.0f)
//   );
//
//   // Up vector
//   glm::vec3 upVec = glm::cross(rightVec, moveDirection);
//
//   // Move forward
//   if (direction == FORWARD) {
//       position = position + moveDirection * deltaTime * speed;
//       std::cout << "Position  x: " << position.x << " y: " << position.y << " z: " << position.z << std::endl;
//   }
//   // Move backward
//   if (direction == BACKWARD) {
//       position = position - moveDirection * deltaTime * speed;
//       std::cout << "Position  x: " << position.x << " y: " << position.y << " z: " << position.z << std::endl;
//   }
//   // Strafe right
//   if (direction == RIGHT) {
//       position = position + rightVec * deltaTime * speed;
//       std::cout << "Position  x: " << position.x << " y: " << position.y << " z: " << position.z << std::endl;
//   }
//   // Strafe left
//   if (direction == LEFT) {
//       position = position - rightVec * deltaTime * speed;
//       std::cout << "Position  x: " << position.x << " y: " << position.y << " z: " << position.z << std::endl;
//   }
//   // Go up
//   if (direction == UP) {
//       position = position + upVec * deltaTime * speed;
//       std::cout << "Position  x: " << position.x << " y: " << position.y << " z: " << position.z << std::endl;
//   }
//   // For the next frame, the "last time" will be "now"
//   lastTime = currentTime;
//}
//
//void Camera::mouseMove(GLfloat xOffset, GLfloat yOffset) {
//
//}

Camera::~Camera() {

}

