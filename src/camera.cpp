//********************************************************************************************//
//   Camera, Controls, keyboard and mouse                                                     //
//********************************************************************************************//
#include "camera.h"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

// Initial position : on +Z
glm::vec3 cameraPosition = glm::vec3(0, 0, 5);
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;

glm::mat4 getViewMatrix() {
    return ViewMatrix;
}

glm::mat4 getProjectionMatrix() {
    return ProjectionMatrix;
}

void handleControls(GLFWwindow *window) {
    // glfwGetTime is called only once, the first time this function is called
   static double lastTime = glfwGetTime();

   // Compute time difference between current and last frame
   double currentTime = glfwGetTime();
   float deltaTime = float(currentTime - lastTime);

   // Get mouse position
   double xpos, ypos;
   glfwGetCursorPos(window, &xpos, &ypos);

   // Reset mouse position for next frame
   glfwSetCursorPos(window, 640/2, 640/2);

   // Compute new orientation
   horizontalAngle = horizontalAngle + mouseSpeed * float(640/2 - xpos);
   verticalAngle   = verticalAngle   + mouseSpeed * float(640/2 - ypos);

   // Direction : Spherical coordinates to Cartesian coordinates conversion
   glm::vec3 cameraDirection(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
   );

   // Right vector
   glm::vec3 cameraRight = glm::vec3(
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        cos(horizontalAngle - 3.14f/2.0f)
   );

   // Up vector
   glm::vec3 cameraUp = glm::cross(cameraRight, cameraDirection);

   // Move forward
   if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS) {
        cameraPosition = cameraPosition + cameraDirection * deltaTime * speed;
        std::cout << "Position  x: " << cameraPosition.x << " y: " << cameraPosition.y << " z: " << cameraPosition.z << std::endl;
   }
   // Move backward
   if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS) {
        cameraPosition = cameraPosition - cameraDirection * deltaTime * speed;
        std::cout << "Position  x: " << cameraPosition.x << " y: " << cameraPosition.y << " z: " << cameraPosition.z << std::endl;
   }
   // Strafe right
   if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS) {
        cameraPosition = cameraPosition + cameraRight * deltaTime * speed;
        std::cout << "Position  x: " << cameraPosition.x << " y: " << cameraPosition.y << " z: " << cameraPosition.z << std::endl;
   }
   // Strafe left
   if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS) {
        cameraPosition = cameraPosition - cameraRight * deltaTime * speed;
        std::cout << "Position  x: " << cameraPosition.x << " y: " << cameraPosition.y << " z: " << cameraPosition.z << std::endl;
   }

   float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

   // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
   ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
   // Camera matrix
   ViewMatrix       = glm::lookAt(
           cameraPosition,                   // Camera is here
           cameraPosition + cameraDirection, // and looks here : at the same position, plus "direction"
           cameraUp                          // Head is up (set to 0,-1,0 to look upside-down)
   );

   // For the next frame, the "last time" will be "now"
   lastTime = currentTime;
}
