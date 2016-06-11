/*
 * light.cpp
 *
 *  Created on: 2016. jún. 5.
 *      Author: SilverBlade
 */

#include "PointLight.h"

PointLight::PointLight() {
    this->lightPos = glm::vec3(0.0, 0.0, 0.0);
    this->ambient = glm::vec3(1.0, 1.0, 1.0);
    this->diffuse = glm::vec3(1.0, 1.0, 1.0);
    this->specular = glm::vec3(1.0, 1.0, 1.0);
}

PointLight::PointLight(glm::vec3 lightPos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
    this->lightPos = lightPos;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}

void PointLight::setLightPos(glm::vec3 lightPos) {
    this->lightPos = lightPos;
}

glm::vec3 PointLight::getLightPos() {
    return this->lightPos;
}

PointLight::~PointLight() {

}

