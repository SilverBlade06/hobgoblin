/*
 * Material.cpp
 *
 *  Created on: 2016. jún. 7.
 *      Author: SilverBlade
 */

#include "Material.h"

Material::Material(GLint diffuse, GLint specular, GLfloat shininess) {
    this->diffuse   = diffuse;
    this->specular  = specular;
    this->shininess = shininess;
}

GLint Material::getDiffuse() const {
    return diffuse;
}

void Material::setDiffuse(GLint diffuse) {
    this->diffuse = diffuse;
}

GLint Material::getSpecular() const {
    return specular;
}

void Material::setSpecular(GLint specular) {
    this->specular = specular;
}

GLfloat Material::getShininess() const {
    return shininess;
}

void Material::setShininess(GLfloat shininess) {
    this->shininess = shininess;
}

Material::~Material() {

}

