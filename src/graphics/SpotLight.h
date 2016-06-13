/*
 * SpotLight.h
 *
 *  Created on: 2016. j�n. 12.
 *      Author: SilverBlade
 */

#ifndef SRC_GRAPHICS_SPOTLIGHT_H_
#define SRC_GRAPHICS_SPOTLIGHT_H_

#include "Light.h"

class SpotLight: public Light {
private:
    glm::vec3 lightPos;
    glm::vec3 lightDir;
    GLfloat cutOff;
    GLfloat outerCutOff;
public:
    SpotLight();
    SpotLight(glm::vec3 lightPos, glm::vec3 lightDir, glm::vec3 ambient,
            glm::vec3 diffuse, glm::vec3 specular, GLfloat cutOff, GLfloat outerCutOff);
    GLfloat getCutOff() const;
    void setCutoff(GLfloat cutOff);
    const glm::vec3& getLightDir() const;
    GLfloat getOuterCutoff() const;
    void setOuterCutoff(GLfloat outerCutOff);
    void setLightDir(const glm::vec3& lightDir);
    const glm::vec3& getLightPos() const;
    void setLightPos(const glm::vec3& lightPos);
    virtual ~SpotLight();
};

#endif /* SRC_GRAPHICS_SPOTLIGHT_H_ */
