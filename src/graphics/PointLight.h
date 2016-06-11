/*
 * light.h
 *
 *  Created on: 2016. jún. 5.
 *      Author: SilverBlade
 */

#ifndef SRC_GRAPHICS_POINTLIGHT_H_
#define SRC_GRAPHICS_POINTLIGHT_H_

// OpenGL/Graphic libraries
// Include GLEW (ALWAYS INCLUDE **BEFORE** GLFW)
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp>

#include "Light.h"

class PointLight : public Light {
private:
    glm::vec3 lightPos;
public:
    PointLight();
    PointLight(glm::vec3 lightPos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    void setLightPos(glm::vec3 lightPos);
    glm::vec3 getLightPos();
    ~PointLight();
};

#endif /* SRC_GRAPHICS_POINTLIGHT_H_ */
