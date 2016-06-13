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
    this->constant = 1.0;
    this->linear = 0.09;
    this->quadratic = 0.032;
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
    this->constant = 1.0;
    this->linear = 0.09;
    this->quadratic = 0.032;
}

SpotLight::SpotLight(glm::vec3 lightPos, glm::vec3 lightDir, glm::vec3 ambient,
        glm::vec3 diffuse, glm::vec3 specular, GLfloat cutOff, GLfloat outerCutOff,
        GLfloat constant, GLfloat linear, GLfloat quadratic) {
    this->lightPos = lightPos;
    this->lightDir = lightDir;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->cutOff = glm::cos(glm::radians(cutOff));
    this->outerCutOff = glm::cos(glm::radians(outerCutOff));
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
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

GLfloat SpotLight::getConstant() const {
    return constant;
}

void SpotLight::setConstant(GLfloat constant) {
    this->constant = constant;
}

void SpotLight::setCutOff(GLfloat cutOff) {
    this->cutOff = cutOff;
}

GLfloat SpotLight::getLinear() const {
    return linear;
}

void SpotLight::setLinear(GLfloat linear) {
    this->linear = linear;
}

GLfloat SpotLight::getOuterCutOff() const {
    return outerCutOff;
}

void SpotLight::setOuterCutOff(GLfloat outerCutOff) {
    this->outerCutOff = outerCutOff;
}

GLfloat SpotLight::getQuadratic() const {
    return quadratic;
}

void SpotLight::setQuadratic(GLfloat quadratic) {
    this->quadratic = quadratic;
}

GLfloat SpotLight::getOuterCutoff() const {
    return outerCutOff;
}

void SpotLight::setOuterCutoff(GLfloat outerCutoff) {
    this->outerCutOff = outerCutoff;
}

SpotLight::~SpotLight() {

}
