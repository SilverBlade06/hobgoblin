/*
 * lightController.h
 *
 *  Created on: 2016. jún. 6.
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

#include "../graphics/Light.h"

class LightController {
private:
    GLFWwindow* window;
    Light* light;
public:
    LightController(GLFWwindow* window, Light* light);
    void control();
    virtual ~LightController();
};

#endif /* SRC_CONTROLS_LIGHTCONTROLLER_H_ */
