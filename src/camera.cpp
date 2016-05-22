//********************************************************************************************//
//   Camera, Controls, keyboard and mouse                                                TODO //
//********************************************************************************************//
#include "camera.h"

//extern struct Vector;
//
//// horizontal angle : toward -Z
//float horizontalAngle = 3.14f;
//// vertical angle : 0, look at the horizon
//float verticalAngle = 0.0f;
//// Initial Field of View
//float initialFoV = 45.0f;
//
//float speed = 3.0f; // 3 units / second
//float mouseSpeed = 0.005f;
//
//Vector cameraPos(0,0,5);
//Vector cameraDirection;
//Vector cameraRight(
//        sin(horizontalAngle - 3.14f/2.0f),
//        0,
//        cos(horizontalAngle - 3.14f/2.0f));
//Vector cameraUp = (cameraDirection % cameraRight) / ((cameraDirection % cameraRight)).length();
//
//double lastTime = glfwGetTime();
//
//void handleCameraView(GLFWwindow* window) {
//
//   double currentTime = glfwGetTime();
//   double deltaTime = double(currentTime - lastTime);
//
//   // Get mouse position
//   double xpos, ypos;
//   glfwGetCursorPos(window, &xpos, &ypos);
//
//   // Reset mouse position for next frame
//   glfwSetCursorPos(window, 640/2, 640/2);
//
//   // Compute new orientation
//   horizontalAngle = horizontalAngle + mouseSpeed * deltaTime * float(640/2 - xpos);
//   verticalAngle   = verticalAngle + mouseSpeed * deltaTime * float(640/2 - ypos);
//
//   cameraDirection.x = cos(verticalAngle) * sin(horizontalAngle);
//   cameraDirection.y = sin(verticalAngle);
//   cameraDirection.z = cos(verticalAngle) * cos(horizontalAngle);
//
//   cameraRight.x = sin(horizontalAngle - 3.14f/2.0f);
//   cameraRight.y = 0;
//   cameraRight.z = cos(horizontalAngle - 3.14f/2.0f);
//
//   cameraUp = (cameraDirection % cameraRight) / ((cameraDirection % cameraRight)).length();
//
//   // Move forward
//   if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
//       cameraPos = cameraPos + cameraDirection * deltaTime * speed;
//   }
//   // Move backward
//   if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
//       cameraPos = cameraPos - cameraDirection * deltaTime * speed;
//   }
//   // Strafe right
//   if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
//       cameraPos = cameraPos + cameraRight * deltaTime * speed;
//   }
//   // Strafe left
//   if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
//       cameraPos = cameraPos - cameraRight * deltaTime * speed;
//   }
//
//   gluLookAt(
//           cameraPos.x,
//           cameraPos.y,
//           cameraPos.z,
//           cameraPos.x + cameraDirection.x,
//           cameraPos.x + cameraDirection.y,
//           cameraPos.x + cameraDirection.z,
//           cameraUp.x,
//           cameraUp.y,
//           cameraUp.z);
//
////   // Projection matrix : 45&deg; Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
////   ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
////   // Camera matrix
////   ViewMatrix       = glm::lookAt(
////       position,           // Camera is here
////       position+direction, // and looks here : at the same position, plus "direction"
////       up                  // Head is up (set to 0,-1,0 to look upside-down)
////   );
//
//   lastTime = currentTime;
//
//}
