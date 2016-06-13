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
    this->cutOff = glm::cos(glm::radians(12.5f));
    this->outerCutOff = glm::cos(glm::radians(15.0));
}

SpotLight::SpotLight(glm::vec3 lightPos, glm::vec3 lightDir, glm::vec3 ambient,
        glm::vec3 diffuse, glm::vec3 specular, GLfloat cutOff, GLfloat outerCutOff) {
    this->lightPos = lightPos;
    this->lightDir = lightDir;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->cutOff = glm::cos(glm::radians(cutOff));
    this->outerCutOff = glm::cos(glm::radians(outerCutOff));
}

GLfloat SpotLight::getCutOff() const {
    return cutOff;
}

void SpotLight::setCutoff(GLfloat cutOff) {
    this->cutOff = cutOff;
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

GLfloat SpotLight::getOuterCutoff() const {
    return outerCutOff;
}

void SpotLight::setOuterCutoff(GLfloat outerCutoff) {
    this->outerCutOff = outerCutoff;
}
