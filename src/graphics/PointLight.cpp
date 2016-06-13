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
    this->constant = 1.0;
    this->linear = 0.09;
    this->quadratic = 0.032;
    this->enabled = true;
}

PointLight::PointLight(glm::vec3 lightPos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
    this->lightPos = lightPos;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->constant = 1.0;
    this->linear = 0.09;
    this->quadratic = 0.032;
    this->enabled = true;
}

PointLight::PointLight(glm::vec3 lightPos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
        GLfloat constant, GLfloat linear, GLfloat quadratic) {
    this->lightPos = lightPos;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
    this->enabled = true;
}

void PointLight::setLightPos(glm::vec3 lightPos) {
    this->lightPos = lightPos;
}

glm::vec3 PointLight::getLightPos() {
    return this->lightPos;
}

PointLight::~PointLight() {

}

GLfloat PointLight::getConstant() const {
    return constant;
}

void PointLight::setConstant(GLfloat constant) {
    this->constant = constant;
}

GLfloat PointLight::getLinear() const {
    return linear;
}

void PointLight::setLinear(GLfloat linear) {
    this->linear = linear;
}

GLfloat PointLight::getQuadratic() const {
    return quadratic;
}

void PointLight::setQuadratic(GLfloat quadratic) {
    this->quadratic = quadratic;
}
