/*
 * light.h
 *
 *  Created on: 2016. jún. 5.
 *      Author: SilverBlade
 */

#ifndef SRC_GRAPHICS_POINTLIGHT_H_
#define SRC_GRAPHICS_POINTLIGHT_H_

#include "Light.h"

class PointLight : public Light {
protected:
    glm::vec3 lightPos;

    // Attenuation
    GLfloat constant;
    GLfloat linear;
    GLfloat quadratic;
public:
    PointLight();
    PointLight(glm::vec3 lightPos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    PointLight(glm::vec3 lightPos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
            GLfloat constant, GLfloat linear, GLfloat quadratic);
    void setLightPos(glm::vec3 lightPos);
    glm::vec3 getLightPos();
    ~PointLight();
    GLfloat getConstant() const;
    void setConstant(GLfloat constant);
    GLfloat getLinear() const;
    void setLinear(GLfloat linear);
    GLfloat getQuadratic() const;
    void setQuadratic(GLfloat quadratic);
};

#endif /* SRC_GRAPHICS_POINTLIGHT_H_ */
