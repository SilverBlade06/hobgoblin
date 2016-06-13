/*
 * light.cpp
 *
 *  Created on: 2016. jún. 5.
 *      Author: SilverBlade
 */

#include "DirectionLight.h"

DirectionLight::DirectionLight() {
    this->lightDir = glm::vec3(0.0, 0.0, 0.0);
    this->ambient = glm::vec3(1.0, 1.0, 1.0);
    this->diffuse = glm::vec3(1.0, 1.0, 1.0);
    this->specular = glm::vec3(1.0, 1.0, 1.0);
    this->enabled = true;
}

DirectionLight::DirectionLight(glm::vec3 lightDir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
    this->lightDir = lightDir;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->enabled = true;
}

void DirectionLight::setLightDir(glm::vec3 lightDir) {
    this->lightDir = lightDir;
}

glm::vec3 DirectionLight::getLightDir() {
    return this->lightDir;
}

DirectionLight::~DirectionLight() {

}

