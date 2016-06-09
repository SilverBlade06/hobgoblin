/*
 * lightController.cpp
 *
 *  Created on: 2016. jún. 6.
 *      Author: SilverBlade
 */

#include "LightController.h"

extern bool keys[1024];

LightController::LightController(Light* light) {
   this->light = light;
}

void LightController::control(GLFWwindow* window, float deltaTime) {
   float speed = 3.0f; // 3 units / second

   // Move forward
   if (keys[GLFW_KEY_I]) {
       light->setLightPos(light->getLightPos() + glm::vec3(0,0,-1) * deltaTime * speed);
   }
   // Move backward
   if (keys[GLFW_KEY_K]) {
       light->setLightPos(light->getLightPos() - glm::vec3(0,0,-1) * deltaTime * speed);
   }
   // Strafe right
   if (keys[GLFW_KEY_L]) {
       light->setLightPos(light->getLightPos() + glm::vec3(1,0,0) * deltaTime * speed);
   }
   // Strafe left
   if (keys[GLFW_KEY_J]) {
       light->setLightPos(light->getLightPos() - glm::vec3(1,0,0) * deltaTime * speed);
   }
   // Go up
   if (keys[GLFW_KEY_O]) {
       light->setLightPos(light->getLightPos() + glm::vec3(0,1,0) * deltaTime * speed);
   }
   // Go down
   if (keys[GLFW_KEY_U]) {
       light->setLightPos(light->getLightPos() - glm::vec3(0,1,0) * deltaTime * speed);
   }

}

LightController::~LightController() {

}
