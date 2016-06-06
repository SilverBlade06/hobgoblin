/*
 * light.cpp
 *
 *  Created on: 2016. jún. 5.
 *      Author: SilverBlade
 */

#include "light.h"

Light::Light() {
    this->lightPos = glm::vec3(0.0, 0.0, 0.0);
    this->ambient = glm::vec3(1.0, 1.0, 1.0);
    this->diffuse = glm::vec3(1.0, 1.0, 1.0);
    this->specular = glm::vec3(1.0, 1.0, 1.0);
}

Light::Light(glm::vec3 lightPos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
    this->lightPos = lightPos;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}

void Light::setLightPos(glm::vec3 lightPos) {
    this->lightPos = lightPos;
}

glm::vec3 Light::getLightPos() {
    return this->lightPos;
}

void Light::setAmbient(glm::vec3 ambient) {
    this->ambient = ambient;
}

glm::vec3 Light::getAmbient() {
    return this->ambient;
}

void Light::setDiffuse(glm::vec3 diffuse) {
    this->diffuse = diffuse;
}

glm::vec3 Light::getDiffuse() {
    return this->diffuse;
}

void Light::setSpecular(glm::vec3 specular) {
    this->specular = specular;
}

glm::vec3 Light::getSpecular() {
    return this->specular;
}
Light::~Light() {

}

