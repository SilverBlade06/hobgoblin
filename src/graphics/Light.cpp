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
}

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
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
    // TODO Auto-generated destructor stub
}

