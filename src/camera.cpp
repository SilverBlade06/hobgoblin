//********************************************************************************************//
//   Camera, Controls, keyboard and mouse                                                     //
//********************************************************************************************//
#include "camera.h"

extern glm::vec3 lightPos; //TODO

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

int windowWidth = 640;
int windowHeight = 480;

// Initial position : on +Z
glm::vec3 cameraPosition = glm::vec3(0, 0, 3);
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;

int getWindowWidth() {
    return windowWidth;
}

int getWindowHeight() {
    return windowHeight;
}

glm::mat4 getViewMatrix() {
    return ViewMatrix;
}

glm::mat4 getProjectionMatrix() {
    return ProjectionMatrix;
}

glm::vec3 getCameraPosition() {
    return cameraPosition;
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
   glfwSetCursorPos(window, windowWidth/2, windowHeight/2);

   // Compute new orientation
   horizontalAngle = horizontalAngle + mouseSpeed * float(windowWidth/2 - xpos);
   verticalAngle   = verticalAngle   + mouseSpeed * float(windowHeight/2 - ypos);

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
   if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS) {
        cameraPosition = cameraPosition + cameraDirection * deltaTime * speed;
        std::cout << "Position  x: " << cameraPosition.x << " y: " << cameraPosition.y << " z: " << cameraPosition.z << std::endl;
   }
   // Move backward
   if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS) {
        cameraPosition = cameraPosition - cameraDirection * deltaTime * speed;
        std::cout << "Position  x: " << cameraPosition.x << " y: " << cameraPosition.y << " z: " << cameraPosition.z << std::endl;
   }
   // Strafe right
   if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS) {
        cameraPosition = cameraPosition + cameraRight * deltaTime * speed;
        std::cout << "Position  x: " << cameraPosition.x << " y: " << cameraPosition.y << " z: " << cameraPosition.z << std::endl;
   }
   // Strafe left
   if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS) {
        cameraPosition = cameraPosition - cameraRight * deltaTime * speed;
        std::cout << "Position  x: " << cameraPosition.x << " y: " << cameraPosition.y << " z: " << cameraPosition.z << std::endl;
   }
   // Go up
   if (glfwGetKey( window, GLFW_KEY_SPACE ) == GLFW_PRESS) {
        cameraPosition = cameraPosition + cameraUp * deltaTime * speed;
        std::cout << "Position  x: " << cameraPosition.x << " y: " << cameraPosition.y << " z: " << cameraPosition.z << std::endl;
   }

   //*****
   // Move forward
   if (glfwGetKey( window, GLFW_KEY_I ) == GLFW_PRESS) {
       lightPos = lightPos + glm::vec3(0,0,-1) * deltaTime * speed;
   }
   // Move backward
   if (glfwGetKey( window, GLFW_KEY_K ) == GLFW_PRESS) {
       lightPos = lightPos - glm::vec3(0,0,-1) * deltaTime * speed;
   }
   // Strafe right
   if (glfwGetKey( window, GLFW_KEY_L ) == GLFW_PRESS) {
       lightPos = lightPos + glm::vec3(1,0,0) * deltaTime * speed;
   }
   // Strafe left
   if (glfwGetKey( window, GLFW_KEY_J ) == GLFW_PRESS) {
       lightPos = lightPos - glm::vec3(1,0,0) * deltaTime * speed;
   }
   // Go up
   if (glfwGetKey( window, GLFW_KEY_O ) == GLFW_PRESS) {
       lightPos = lightPos + glm::vec3(0,1,0) * deltaTime * speed;
   }

   if (glfwGetKey( window, GLFW_KEY_U ) == GLFW_PRESS) {
       lightPos = lightPos - glm::vec3(0,1,0) * deltaTime * speed;
   }
   //*****

   float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

   // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
   ProjectionMatrix = glm::perspective(FoV, (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
   // Camera matrix
   ViewMatrix       = glm::lookAt(
           cameraPosition,                   // Camera is here
           cameraPosition + cameraDirection, // and looks here : at the same position, plus "direction"
           cameraUp                          // Head is up (set to 0,-1,0 to look upside-down)
   );

   // For the next frame, the "last time" will be "now"
   lastTime = currentTime;
}
