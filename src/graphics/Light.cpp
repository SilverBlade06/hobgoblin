/*
 * Light.cpp
 *
 *  Created on: 2016. jún. 11.
 *      Author: SilverBlade
 */

#include "Light.h"

Light::Light() {
   this->ambient = glm::vec3(1.0, 1.0, 1.0);
   this->diffuse = glm::vec3(1.0, 1.0, 1.0);
   this->specular = glm::vec3(1.0, 1.0, 1.0);
   this->enabled = true;
}

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
   this->ambient = ambient;
   this->diffuse = diffuse;
   this->specular = specular;
   this->enabled = true;
}

void Light::setAmbient(glm::vec3 ambient) {
   this->ambient = ambient;
}

glm::vec3 Light::getAmbient() {
   if (!enabled) {
       return glm::vec3(0.0, 0.0, 0.0);
   }
   return this->ambient;
}

void Light::setDiffuse(glm::vec3 diffuse) {
   this->diffuse = diffuse;
}

glm::vec3 Light::getDiffuse() {
   if (!enabled) {
       return glm::vec3(0.0, 0.0, 0.0);
   }
   return this->diffuse;
}

void Light::setSpecular(glm::vec3 specular) {
   this->specular = specular;
}

glm::vec3 Light::getSpecular() {
   if (!enabled) {
       return glm::vec3(0.0, 0.0, 0.0);
   }
   return this->specular;
}

bool Light::isEnabled() const {
   return enabled;
}

void Light::setEnabled(bool enabled) {
   this->enabled = enabled;
}

Light::~Light() {

}
