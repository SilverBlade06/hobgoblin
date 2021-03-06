/*
 * lightController.h
 *
 *  Created on: 2016. j�n. 6.
 *      Author: SilverBlade
 */

#ifndef SRC_CONTROLS_LIGHTCONTROLLER_H_
#define SRC_CONTROLS_LIGHTCONTROLLER_H_

// OpenGL/Graphic libraries
// Include GLEW (ALWAYS INCLUDE **BEFORE** GLFW)
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp>

#include "../graphics/PointLight.h"

class LightController {
private:
    PointLight* light;
public:
    LightController(PointLight* light);
    void control(GLFWwindow* window, float deltaTime);
    virtual ~LightController();
};

#endif /* SRC_CONTROLS_LIGHTCONTROLLER_H_ */
