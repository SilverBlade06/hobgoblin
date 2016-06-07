/*
 * Material.cpp
 *
 *  Created on: 2016. jún. 7.
 *      Author: SilverBlade
 */

#include "Material.h"

Material::Material() {
    this->ambient   = glm::vec3(1.0, 1.0, 1.0);
    this->diffuse   = glm::vec3(1.0, 1.0, 1.0);
    this->specular  = glm::vec3(1.0, 1.0, 1.0);
    this->shininess = 32.0;
}

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLfloat shininess) {
    this->ambient   = ambient;
    this->diffuse   = diffuse;
    this->specular  = specular;
    this->shininess = shininess;
}

const glm::vec3& Material::getAmbient() const {
    return ambient;
}

void Material::setAmbient(const glm::vec3& ambient) {
    this->ambient = ambient;
}

const glm::vec3& Material::getDiffuse() const {
    return diffuse;
}

void Material::setDiffuse(const glm::vec3& diffuse) {
    this->diffuse = diffuse;
}

float Material::getShininess() const {
    return shininess;
}

void Material::setShininess(float shininess) {
    this->shininess = shininess;
}

const glm::vec3& Material::getSpecular() const {
    return specular;
}

void Material::setSpecular(const glm::vec3& specular) {
    this->specular = specular;
}

Material::~Material() {

}

