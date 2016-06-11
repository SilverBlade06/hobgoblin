/*
 * Light.h
 *
 *  Created on: 2016. jún. 11.
 *      Author: SilverBlade
 */

#ifndef SRC_GRAPHICS_LIGHT_H_
#define SRC_GRAPHICS_LIGHT_H_

// OpenGL/Graphic libraries
// Include GLEW (ALWAYS INCLUDE **BEFORE** GLFW)
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp>

class Light {
protected:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
public:
    Light();
    Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    void setAmbient(glm::vec3 ambient);
    glm::vec3 getAmbient();
    void setDiffuse(glm::vec3 diffuse);
    glm::vec3 getDiffuse();
    void setSpecular(glm::vec3 specular);
    glm::vec3 getSpecular();
    virtual ~Light();
};

#endif /* SRC_GRAPHICS_LIGHT_H_ */
