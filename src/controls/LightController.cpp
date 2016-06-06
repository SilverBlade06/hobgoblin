/*
 * lightController.cpp
 *
 *  Created on: 2016. jún. 6.
 *      Author: SilverBlade
 */

#include "LightController.h"

LightController::LightController(GLFWwindow* window, Light* light) {
   this->window = window;
   this->light = light;
}

void LightController::control() {
   float speed = 3.0f; // 3 units / second
    // glfwGetTime is called only once, the first time this function is called
   static double lastTime = glfwGetTime();

   // Compute time difference between current and last frame
   double currentTime = glfwGetTime();
   float deltaTime = float(currentTime - lastTime);

   // Move forward
   if (glfwGetKey( window, GLFW_KEY_I ) == GLFW_PRESS) {
       light->setLightPos(light->getLightPos() + glm::vec3(0,0,-1) * deltaTime * speed);
   }
   // Move backward
   if (glfwGetKey( window, GLFW_KEY_K ) == GLFW_PRESS) {
       light->setLightPos(light->getLightPos() - glm::vec3(0,0,-1) * deltaTime * speed);
   }
   // Strafe right
   if (glfwGetKey( window, GLFW_KEY_L ) == GLFW_PRESS) {
       light->setLightPos(light->getLightPos() + glm::vec3(1,0,0) * deltaTime * speed);
   }
   // Strafe left
   if (glfwGetKey( window, GLFW_KEY_J ) == GLFW_PRESS) {
       light->setLightPos(light->getLightPos() - glm::vec3(1,0,0) * deltaTime * speed);
   }
   // Go up
   if (glfwGetKey( window, GLFW_KEY_O ) == GLFW_PRESS) {
       light->setLightPos(light->getLightPos() + glm::vec3(0,1,0) * deltaTime * speed);
   }

   if (glfwGetKey( window, GLFW_KEY_U ) == GLFW_PRESS) {
       light->setLightPos(light->getLightPos() - glm::vec3(0,1,0) * deltaTime * speed);
   }

   lastTime = currentTime;
}

LightController::~LightController() {

}
