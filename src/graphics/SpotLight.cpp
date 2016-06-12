/*
 * SpotLight.cpp
 *
 *  Created on: 2016. jún. 12.
 *      Author: SilverBlade
 */

#include "SpotLight.h"

SpotLight::SpotLight() {
    this->lightPos = glm::vec3(0.0, 0.0, 0.0);
    this->lightDir = glm::vec3(0.0, 0.0, 0.0);
    this->ambient = glm::vec3(1.0, 1.0, 1.0);
    this->diffuse = glm::vec3(1.0, 1.0, 1.0);
    this->specular = glm::vec3(1.0, 1.0, 1.0);
    this->cutoff = glm::cos(glm::radians(12.5));
}

SpotLight::SpotLight(glm::vec3 lightPos, glm::vec3 lightDir, glm::vec3 ambient,
        glm::vec3 diffuse, glm::vec3 specular, GLfloat cutoff) {
    this->lightPos = lightPos;
    this->lightDir = lightDir;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->cutoff = glm::cos(glm::radians(cutoff));
}

GLfloat SpotLight::getCutoff() const {
    return cutoff;
}

void SpotLight::setCutoff(GLfloat cutoff) {
    this->cutoff = cutoff;
}

const glm::vec3& SpotLight::getLightDir() const {
    return lightDir;
}

void SpotLight::setLightDir(const glm::vec3& lightDir) {
    this->lightDir = lightDir;
}

const glm::vec3& SpotLight::getLightPos() const {
    return lightPos;
}

void SpotLight::setLightPos(const glm::vec3& lightPos) {
    this->lightPos = lightPos;
}

SpotLight::~SpotLight() {

}

