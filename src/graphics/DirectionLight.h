/*
 * light.h
 *
 *  Created on: 2016. jún. 5.
 *      Author: SilverBlade
 */

#ifndef SRC_GRAPHICS_DIRECTIONLIGHT_H_
#define SRC_GRAPHICS_DIRECTIONLIGHT_H_

#include "Light.h"

class DirectionLight : public Light {
private:
    glm::vec3 lightDir;
public:
    DirectionLight();
    DirectionLight(glm::vec3 lightDir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    void setLightDir(glm::vec3 lightDir);
    glm::vec3 getLightDir();
    ~DirectionLight();
};

#endif /* SRC_GRAPHICS_DIRECTIONLIGHT_H_ */
