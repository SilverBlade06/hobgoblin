/*
 * light.h
 *
 *  Created on: 2016. jún. 5.
 *      Author: SilverBlade
 */

#ifndef SRC_GRAPHICS_LIGHT_H_
#define SRC_GRAPHICS_LIGHT_H_

class Light {
private:
    glm::vec3 lightPos;
public:
    Light();
    virtual ~Light();
};

#endif /* SRC_GRAPHICS_LIGHT_H_ */
